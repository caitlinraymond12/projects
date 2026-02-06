`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 10/15/2025 02:50:46 PM
// Design Name: 
// Module Name: divider_top
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


module divider_top(
    input [nBit-1:0]A,
    input [nBit-1:0]B,
    input clk,
    input reset,
    output [nBit-1:0] Qout, 
    output [nBit-1:0] Rout
    );
    
    parameter nBit = 7;
    
    wire [14:0] control_word;
    wire sub_MSB, counter_MSB;
    wire [nBit-1:0] Q, R;
    
    
    datapath #(nBit) dp(.clk(clk), .A(A), .B(B), .ctrlWord(control_word), .msbSub(sub_MSB), .msbCtr(counter_MSB), .Q(Q),.R(R));
    controller ctrl_unit(.clk(clk), .reset(reset), .sub_MSB(sub_MSB), .counter_MSB(counter_MSB), .control_word(control_word));

    assign Qout = Q;
    assign Rout = R;
                                
 
endmodule