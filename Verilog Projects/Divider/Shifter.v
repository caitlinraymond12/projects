`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 09/29/2025 04:12:53 PM
// Design Name: 
// Module Name: Shifter
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


module Shifter(
    input [nBit-1:0] In,
    input clk,
    input load,
    input clr,
    input sl,
    input sr,
    input shiftIn,
    output reg [nBit-1:0] out
    );
    parameter nBit = 16;
    always @(negedge clk)begin
        if(clr)
            out <= 10'b0000000000;
        else begin  
            if(load)
                out <= In;
            else if(sl)
                out <= {out[nBit-2:0], shiftIn};
            else if(sr)
                out <= {shiftIn, out[nBit-1]};
            else
                out <= out;
        end
    end
endmodule
