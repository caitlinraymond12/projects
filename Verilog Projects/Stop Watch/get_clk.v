`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 09/22/2025 03:22:29 PM
// Design Name: 
// Module Name: get_clk
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


module get_clk(
    input clk_base,
    input reset,
    input stop,
    input [nBit-1:0] limit,
    output reg clk_out
    );
    parameter nBit = 18;
    reg[nBit-1:0] clk_counter;
    
    always@(posedge clk_base, posedge reset, posedge stop) begin
        if (reset) begin
            clk_counter <= 0;
            clk_out <= 1'b1;
        end
        else begin
            if(stop)
                clk_counter <= clk_counter;
            else begin
                if(clk_counter == limit-1) begin
                    clk_out <= ~clk_out;
                    clk_counter <= 0;
                end
                else
                    clk_counter <= clk_counter + 1'b1;
                end
        end
     end        
endmodule
