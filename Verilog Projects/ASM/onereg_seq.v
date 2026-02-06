`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 10/20/2025 03:25:05 PM
// Design Name: 
// Module Name: asm_onereg
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



module onereg_seq(
    input  A,
    input  B,
    input  clk, 
    input  reset,
    output reg Out
);

    parameter s0 = 3'b000, s1 = 3'b001, s2 = 3'b010, s3 = 3'b011, s4 = 3'b100;

    reg [2:0] state;


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
