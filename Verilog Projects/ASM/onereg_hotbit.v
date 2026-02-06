`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 10/22/2025 11:16:53 PM
// Design Name: 
// Module Name: onereg_hotbit
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

module onereg_hotbit(
    input  A,
    input  B,
    input  clk, 
    input  reset,
    output reg Out
);

    parameter s0 = 5'b00001,s1 = 5'b00010, s2 = 5'b00100, s3 = 5'b01000, s4 = 5'b10000;

    reg [4:0] state;

    
       always @(posedge clk or posedge reset) begin
        if (reset) begin
            state <= s0;
            Out <= 1'b0;
        end
        else begin
            Out <= 1'b0;
            case(state)
                s0: begin
                    if(A == B)
                        state <= s1;
                    else
                        state <= s0;
               end
               s1: begin
                    if(A == B)
                        state <= s2;
                    else
                        state <= s0;
               end
               s2: begin
                    if(A == B)
                        state <= s3;
                    else
                        state <= s0;
               end
               s3: begin
                    if(A == B) begin
                        state <= s4;
                        Out <= 1'b1;
                    end
                    else
                        state <= s0;       
               end
               s4: begin
                    if(A == B) begin
                        state <= s4;
                        Out <= 1'b1;
                    end
                    else
                        state <= s0;
               end
               default: state <= s0;
            endcase
       end 
    end
 endmodule  
