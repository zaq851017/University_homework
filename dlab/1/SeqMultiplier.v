`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    11:27:40 09/27/2016 
// Design Name: 
// Module Name:    SeqMultiplier 
// Project Name: 
// Target Devices: 
// Tool versions: 
// Description: 
//
// Dependencies: 
//
// Revision: 
// Revision 0.01 - File Created
// Additional Comments: 
//
//////////////////////////////////////////////////////////////////////////////////
module SeqMultiplier(
input wire clk,
input wire enable,
input wire [7:0] A,
input wire [7:0] B,
output wire [15:0] C
    );
reg [7:0] Bmul;
reg [15:0] Cmul;
assign C=Cmul;
always@(posedge clk) 
begin 
	if(enable==0)
		begin
			Cmul=0;
			Bmul=B;
		end
	else if(Bmul)
			begin 
			Cmul=Cmul<<1;
			if(Bmul[7]==1)
				Cmul=Cmul+A;
			Bmul=Bmul<<1;
			end
end			
endmodule
