`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company:
// Engineer:
//
// Create Date: 09/22/2025 03:53:37 PM
// Design Name:
// Module Name: get_digit
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


module get_digit(
    input clk_in,
    input reset,
    input stop,
    input [3:0] limit,
    output reg[3:0] clk_counter  
    );

        always@(posedge clk_in, posedge reset, posedge stop)
        begin
            if(reset)
                begin
                    clk_counter = 0;
                end
            else
                begin
                    if(stop)
                        clk_counter <= clk_counter;
                    else
                        begin
                            if(clk_counter == limit)
                            begin
                               clk_counter <= 0;
                            end
                            else    
                                clk_counter <= clk_counter + 1;
                        end
                  end
            end
   endmodule