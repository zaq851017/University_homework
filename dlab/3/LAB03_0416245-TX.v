`timescale 1ns / 1ps

////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer:
//
// Create Date:   00:12:44 10/10/2016
// Design Name:   MorseDecoder
// Module Name:   C:/GOOD/LAB3-0416245-E3.OK/TX0416245.v
// Project Name:  LAB3-0416245-E3.OK
// Target Device:  
// Tool versions:  
// Description: 
//
// Verilog Test Fixture created by ISE for module: MorseDecoder
//
// Dependencies:
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
////////////////////////////////////////////////////////////////////////////////

module TX0416245;

	// Inputs
	reg clk;
	reg enable;
	reg [79:0] in_bits;

	// Outputs
	wire [34:0] out_text;
	wire valid;

	// Instantiate the Unit Under Test (UUT)
	MorseDecoder uut (
		.clk(clk), 
		.enable(enable), 
		.in_bits(in_bits), 
		.out_text(out_text), 
		.valid(valid)
	);

	initial begin
		// Initialize Inputs
		clk = 0;
		enable = 0;
		in_bits = 80'b11101110001110111011100010111010001010100010000000000000000000000000000000000000;

		// Wait 100 ns for global reset to finish
		#50;
		enable = 1;
		// Add stimulus here
		#300 $finish;
		

	end
	
	// clk
	always
	#2 clk=~clk;
      
endmodule
