`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 09/08/2025 03:55:05 PM
// Design Name: 
// Module Name: fulladder_4bit
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


module fulladder_4bit(
    input [3:0] A,
    input [3:0] B,
    input Sub,
    output [3:0]Sum,
    output Cout
    );
    
    wire b0, b1, b2, b3;
    wire cout0, cout1, cout2, cout3;
   

    
    xor(b0, B[0], Sub);
    xor(b1, B[1], Sub);
    xor(b2, B[2], Sub);
    xor(b3, B[3], Sub);
   
    
    fulladder f0(.A(A[0]), .B(b0), .Cin(Sub), .Sum(Sum[0]), .Cout(cout0));
    fulladder f1(.A(A[1]), .B(b1), .Cin(cout0), .Sum(Sum[1]), .Cout(cout1));
    fulladder f2(.A(A[2]), .B(b2), .Cin(cout1), .Sum(Sum[2]), .Cout(cout2));
    fulladder f3(.A(A[3]), .B(b3), .Cin(cout2), .Sum(Sum[3]), .Cout(cout3));
    
    xor(Cout, cout3, Sub);
    

        
        
    
    
endmodule
