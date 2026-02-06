/*`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 10/23/2025 02:06:55 PM
// Design Name: 
// Module Name: asm_top
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


module asm_top(
    input A,
    input B,
    input clk,
    input reset,
    output OutOG, 
    output OutOH, 
    output OutOS, 
    output OutTG, 
    output OutTH, 
    output OutTS 
    );
    
    
    onereg_gray gray_one(.A(A), .B(B), .clk(clk), .reset(reset), .Out(OutOG));
    onereg_hotbit hotbit_one(.A(A), .B(B), .clk(clk), .reset(reset), .Out(OutOH));
    onereg_seq seq_one(.A(A), .B(B), .clk(clk), .reset(reset), .Out(OutOS));
    
    tworeg_gray gray_two(.A(A), .B(B), .clk(clk), .reset(reset), .Out(OutTG));
    tworeg_hotbit hotbit_two(.A(A), .B(B), .clk(clk), .reset(reset), .Out(OutTH));
    tworeg_seq seq_two(.A(A), .B(B), .clk(clk), .reset(reset), .Out(OutTS));
    
    
    
    
endmodule*/
