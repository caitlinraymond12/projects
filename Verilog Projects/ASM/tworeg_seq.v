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




module tworeg_seq(
    input  A,
    input  B,
    input  clk, 
    input  reset,
    output reg Out
);

    parameter s0 = 3'b000, s1 = 3'b001,s2 = 3'b010, s3 = 3'b011, s4 = 3'b100;

    reg [2:0] state;
    reg [2:0] next_state;

    
    always @(*) begin
        next_state = state;
        case (state)
            s0: next_state = (A == B) ? s1 : s0;
            s1: next_state = (A == B) ? s2 : s0;
            s2: next_state = (A == B) ? s3 : s0;
            s3: next_state = (A == B) ? s4 : s0;
            s4: next_state = (A == B) ? s4 : s0;
            default: next_state = s0;
        endcase
    end

    always @(posedge clk or posedge reset) begin
        if (reset) begin
            state <= s0;
            Out <= 1'b0;
        end
        else begin
            state <= next_state;
            Out <= ((next_state == s4) && (A == B));
        end
    end

endmodule
