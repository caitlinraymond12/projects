`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 09/08/2025 09:47:12 PM
// Design Name: 
// Module Name: twos_complement
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


module twos_complement(
    input [3:0] Num,
    output [3:0] Out
    );
    
    wire n3, n2, n1, n0;
    wire cout;
    xor(n3, Num[3], 1);
    xor(n2, Num[2], 1);
    xor(n1, Num[1], 1);
    xor(n0, Num[0], 1);
    
    fulladder_4bit fa(.A({n3, n2, n1, n0}), .B(4'b0001), .Sub(0), .Sum(Out), .Cout(cout));
    
    
endmodule
