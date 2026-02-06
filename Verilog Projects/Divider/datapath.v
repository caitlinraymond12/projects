`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 10/15/2025 02:56:47 PM
// Design Name: 
// Module Name: datapath
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module datapath #(parameter nBit = 8)(
    input clk,
    input [nBit-1:0] A,
    input [nBit-1:0] B,
    input [14:0] ctrlWord,
    output msbSub,
    output msbCtr,
    output [nBit-1:0] Q, 
    output [nBit-1:0] R
    );


    // not sure if these should be wires instead
    wire [nBit-1:0] outA; // need msb of this for R_SI
    wire [nBit-1:0] outB; // need this for R - B module
    wire [nBit-1:0] outSub;
    wire [nBit-1:0] outFullCtr;
    wire [nBit-1:0] Qin;
    wire [nBit-1:0] Rin;
   
   
    subtractor #(.nBit(nBit)) sub(
    .A(R),
    .B(outB),
    .out(outSub)
    );

   
    Shifter #(.nBit(nBit)) A_shift(
        .clk(clk),
        .In(A),
        .clr(ctrlWord[0]),
        .sr(1'b0), // always low
        .sl(ctrlWord[1]),
        .load(ctrlWord[2]),
        .shiftIn(1'b0),
        .out(outA) // first msb will be used later
    );
     
    Shifter #(.nBit(nBit)) B_shift(
        .clk(clk),
        .In(B),
        .clr(ctrlWord[3]),
        .sr(1'b0), // always low
        .sl(1'b0),
        .load(ctrlWord[4]),
        .shiftIn(1'b0),  
        .out(outB) // feed into A - B
    );

    Shifter #(.nBit(nBit)) R_shift(
        .clk(clk),
        .In(outSub), // output of R-B
        .clr(ctrlWord[5]),
        .sr(1'b0), // always low
        .sl(ctrlWord[6]),
        .load(ctrlWord[7]),
        .shiftIn(outA[nBit-1]), // MSB of wire A_out
        .out(Rin) // this gets fed to A - B + for final out
    );
   
    Shifter #(.nBit(nBit)) Q_shift (
        .clk(clk),
        .In({nBit{1'b0}}), // padded w nBit 0s
        .clr(ctrlWord[8]),
        .sr(1'b0),
        .sl(ctrlWord[9]),
        .load(ctrlWord[10]),
        .shiftIn(ctrlWord[11]),
        .out(Qin)
    );
   
    Shifter #(.nBit(nBit)) Ctr_shift(
        .clk(clk),
        .In(1'b0),
        .clr(ctrlWord[12]),
        .sr(1'b0), // always low
        .sl(ctrlWord[13]),
        .load(ctrlWord[14]),
        .shiftIn(1'b1), // always 1
        .out(outFullCtr)  
    );
   
    assign msbCtr = outFullCtr[nBit-1];
    assign msbSub = outSub[nBit-1];
    assign Q = Qin;
    assign R = Rin;
   

endmodule