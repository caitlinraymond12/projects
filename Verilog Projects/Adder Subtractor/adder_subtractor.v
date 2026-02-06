`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 09/09/2025 01:57:58 PM
// Design Name: 
// Module Name: adder_subtractor
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


module adder_subtractor(
    input [3:0] A,
    input [3:0] B,
    input Sub,
    output [3:0] Sum,
    output Cout
    );

    wire [3:0]out;
    wire [3:0]twosOut;
    
    fulladder_4bit fa0(.A(A), .B(B), .Sub(Sub), .Sum(out), .Cout(Cout));
    twos_complement tc0(.Num(out), .Out(twosOut));
    assign Sum = (Cout && Sub) ? twosOut : out;
   
    
endmodule
