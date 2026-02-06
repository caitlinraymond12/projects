`timescale 1ns / 1ps

////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer:
//
// Create Date:   12:21:22 09/15/2015
// Design Name:   sev_seg_with_clk_top
// Module Name:   C:/ECE414_Toprak/Tutorial2/tb_seven_seg.v
// Project Name:  Tutorial2
// Target Device:  
// Tool versions:  
// Description: 
//
// Verilog Test Fixture created by ISE for module: sev_seg_with_clk_top
//
// Dependencies:
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
////////////////////////////////////////////////////////////////////////////////

module tb_seven_seg;

	// Inputs
	reg [3:0] num_1;
	reg [3:0] num_2;
	reg clk_main;
	reg reset;

	// Outputs
	wire [7:0] sev_seg_leds;
	wire [5:0] led_disable;
	wire [1:0] led_enable;

	// Instantiate the Unit Under Test (UUT)
	sev_seg_with_clk_top uut (
		.num_1(num_1), 
		.num_2(num_2), 
		.clk_main(clk_main), 
		.reset(reset), 
		.sev_seg_leds(sev_seg_leds), 
		.led_disable(led_disable), 
		.led_enable(led_enable)
	);

	initial begin
		// Initialize Inputs
		num_1 = 0;
		num_2 = 0;
		clk_main = 0;
		reset = 0;

		// Wait 100 ns for global reset to finish
		#100;
        
		// Add stimulus here
		
		reset = 1;
		
		#25;
		reset = 0;
		
		#25;
		num_1 = 8;
		num_2 = 3;
		
		#140;
		num_1 = 1;
		num_2 = 15;
		
	end
      
	always 
	  #5 clk_main = ~clk_main;
	
endmodule

