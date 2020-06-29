`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    14:24:24 10/02/2016 
// Design Name: 
// Module Name:    lab2hong 
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
module lab2hong(
    input clk,
    input reset,
    input btn_east,
    input btn_west,
    output  [7:0] led
    );
reg [22:0] counter;
reg signed [7:0] temp;
wire debounce;
assign led = temp;
always @(posedge clk,posedge reset)
begin 
	if(reset)
		counter <=0;
	else 
		counter<=counter+1;
end

assign debounce = &counter ;//all 1--> debounce
always @(posedge clk,posedge reset)
begin 
		if(reset)
			temp<=0;
		else if(debounce && btn_east)
			begin
			if(temp != -8)
			temp<=temp-1;
			else
			temp <= temp;
			end
		else if(debounce && btn_west)
			begin
			if(temp != 7)
			temp<=temp+1;
			else
			temp <= temp;
			end
end			
endmodule
