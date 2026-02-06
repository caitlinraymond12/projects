`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company:
// Engineer:
//
// Create Date: 09/22/2025 03:44:55 PM
// Design Name:
// Module Name: top_stopwatch
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


module top_stopwatch(
    input clk_main,
    input reset,
    input stop,
    input switch,
    output[7:0] sev_seg_leds,
    output[3:0] led_disable,
    output[3:0] led_enable
    );
   
    wire clk_1_10sec, clk_1sec, clk_10sec, clk_1min;
    wire [3:0]digit_1_10sec;
    wire [3:0]digit_1sec;
    wire [3:0]digit_10sec;
    wire [3:0]digit_1min;  
   
   
   
   ip_clk_div clk_5M( // generated core to obtain a slower clk of 5MHz from onboard 100 MHz oscillator.
    .clk_in1(clk_main),       // we assign the external 100 MHz clock to clk_main
    .clk_out1(clk_slow));     // we assign the generated 5 MHz clock to clk_slw


    get_clk #18 clk_1_10s(.stop(stop), .clk_base(clk_slow), .reset(reset), .limit(18'd250000), .clk_out(clk_1_10sec));
    get_digit digit_1_10s(.stop(stop), .clk_in(clk_1_10sec), .reset(reset), .limit(4'b1001), .clk_counter(digit_1_10sec));
   
   
    get_clk #3 clk_1s(.stop(stop), .clk_base(clk_1_10sec), .reset(reset), .limit(3'd5), .clk_out(clk_1sec));
    get_digit digit_1s(.stop(stop), .clk_in(clk_1sec), .reset(reset), .limit(4'b1001), .clk_counter(digit_1sec));
   
   
    get_clk #3 clk_10s(.stop(stop), .clk_base(clk_1sec), .reset(reset), .limit(3'd5), .clk_out(clk_10sec));
    get_digit digit_10s(.stop(stop), .clk_in(clk_10sec), .reset(reset), .limit(4'b0101), .clk_counter(digit_10sec));
   
   
    get_clk #2 clk_1m(.stop(stop), .clk_base(clk_10sec), .reset(reset), .limit(2'd3), .clk_out(clk_1min));
    get_digit digit_1m(.stop(stop), .clk_in(clk_1min), .reset(reset), .limit(4'b1001), .clk_counter(digit_1min));
   
   sev_seg_with_clk_top display(.num_1(digit_1min), .num_2(digit_10sec), .num_3(digit_1sec), .num_4(digit_1_10sec), 
                                .clk_main(clk_slow), .reset(reset), .blink_enable(switch), .stop(stop),
                                .sev_seg_leds(sev_seg_leds), .led_disable(led_disable),
                                .led_enable(led_enable));
    
   
endmodule
