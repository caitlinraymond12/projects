`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 09/29/2025 04:19:26 PM
// Design Name: 
// Module Name: controller
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


module controller(
    input clk,
    input reset,
    input sub_MSB, 
    input counter_MSB,
    output reg[14:0] control_word
   );
    
    
    reg [2:0] state = 3'b000;
  
   
    always @(posedge clk, posedge reset) begin
        //reset state 
        if (reset) begin 
            state <= 3'b000;
            control_word <= 15'b001001100101001; //resets
        end
        
        else begin

        if(state == 3'b000) begin   
            state <= 3'b001;
            control_word <= 15'b001010000110100;   //loads everything. clearing R because we set to 0    
        end
       
        
        //initial state to load and setup
        else if(state == 3'b001) begin  
                    state <= 3'b010;
                    control_word <= 15'b000000000000000;  //sends to dummy state
        end
        
        //state to come to after initial/round of execution
        else if(state == 3'b010) begin
            if(counter_MSB == 1)
                begin 
                    state <= 3'b011;
                    control_word <= 15'b000000000000000;
                end
            else
                begin
                    state <= 3'b100;
                    control_word <= 15'b000000001000010;  //shift a into r
                end
        end
        
        
        //end state. quotient and remainder are found 
        else if(state == 3'b011) begin
            state <= 3'b011;
        end
        
        
        //first step. shift A left into R.
        //already done. give a clock cycle to get results.
        else if(state == 3'b100) begin
            state <= 3'b111;
            control_word <= 15'b000000000000000;
        end
       
        else if(state == 3'b111) begin
                if(sub_MSB == 0)
                    begin
                        state <= 3'b010;
                        control_word <= 15'b010101010000000; //was able to subtract
                    end
                
                else
                    begin
                        state <= 3'b010;
                        control_word <= 15'b010001000000000; //was not able to subtract
                    end
            end
        end
    end
endmodule
