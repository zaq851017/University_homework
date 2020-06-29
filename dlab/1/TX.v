`timescale 1ns / 1ps

////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer:
//
// Create Date:   11:30:05 09/27/2016
// Design Name:   SeqMultiplier
// Module Name:   C:/GOOD/LAB1/TX.v
// Project Name:  LAB1
// Target Device:  
// Tool versions:  
// Description: 
//
// Verilog Test Fixture created by ISE for module: SeqMultiplier
//
// Dependencies:
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
////////////////////////////////////////////////////////////////////////////////

module TX;

	// Outputs
	wire [15:0] C;
	reg [7:0] A;
	reg [7:0] B;
	reg enable;
	reg clk;

	// Instantiate the Unit Under Test (UUT)
	SeqMultiplier uut (
		.C(C),
		.B(B),
		.A(A),
		.clk(clk),
		.enable(enable)
		
	);

	initial begin
	A=0;
	B=0;
	enable=0;
		// Initialize Inputs
		// Wait 100 ns for global reset to finish
		#100;
		  enable=1;
        A=239;
		  B=35;
		#100;
			enable=0;
		#100;
			enable=1;
			A=239;
			B=35;
		// Add stimulus here

	end
	initial begin
		clk = 0;
	end

	always #10 begin 
		clk = ~clk ;
	end
	

      
endmodule

