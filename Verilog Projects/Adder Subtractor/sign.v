`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 09/15/2025 08:10:35 PM
// Design Name: 
// Module Name: sign
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


module sign(
    input Cout,
    input Sub,
    output Overflow,
    output Sign
    );
    
    assign Sign = ((Cout && Sub) ? 1'b1 : 1'b0);
    assign Overflow = ((Cout && !Sub) ? 1'b1 : 1'b0);
    
    
    
endmodule
