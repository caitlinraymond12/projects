`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 09/08/2025 03:39:51 PM
// Design Name: 
// Module Name: fulladder
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


module fulladder(
    input A,
    input B,
    input Cin,
    output Cout,
    output Sum
    );
    
    wire cout0, sum0, cout1;
    
    halfadder ha0(.A(A), .B(B), .Sum(sum0), .Cout(cout0));
    halfadder ha1(.A(sum0), .B(Cin), .Sum(Sum), .Cout(cout1));
    
    or(Cout, cout0, cout1);
    
  
endmodule
