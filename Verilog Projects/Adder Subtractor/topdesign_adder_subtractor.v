`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 09/15/2025 07:21:19 PM
// Design Name: 
// Module Name: topdesign_adder_subtractor
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


module topdesign_adder_subtractor(
    input [3:0] A,
    input [3:0] B,
    input Sub,
    input clk_main,
	input reset,
	output [7:0] sev_seg_leds,
    output [4:0] led_disable,
    output [2:0] led_enable,
    output overflow,
    output negative
    );
    
    wire [3:0] Sum, Cout;
    
    adder_subtractor add_sub(.A(A), .B(B), .Sub(Sub), .Sum(Sum), .Cout(Cout));
    sign sign0(.Cout(Cout), .Sub(Sub), .Overflow(overflow), .Sign(negative));
    sev_seg_with_clk_top sevseg0(.num_1(A), .num_2(B), .num_3(Sum), .clk_main(clk_main), .reset(reset), .sev_seg_leds(sev_seg_leds), .led_disable(led_disable), .led_enable(led_enable));
    
    
endmodule
