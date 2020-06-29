`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: National Chiao Tung University
// Engineer: Chun-Jen Tsai
//
// Create Date:    14:24:54 11/29/2016 
// Design Name: 
// Module Name:    lab9 
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
module lab9(
  input clk,
  input reset,
  input  button,
  output reg[7:0] led,
  output LCD_E,
  output LCD_RS,
  output LCD_RW,
  output [3:0] LCD_D,
  input ROT_A,
  input ROT_B
  );

  // declare system variables
  wire btn_level, btn_pressed;
  reg prev_btn_level;
  reg [127:0] row_A, row_B;
  reg [7:0] led_on[0:7];
  wire rot_event;
  wire rot_right;

  reg [22:0] counter;
  reg [22:0] high_ticks;
  reg frequency; //0 represent 25Hz;1 represent 100Hz;
  reg [2:0] duty_cycles;

  debounce btn_db0(
    .clk(clk),
    .btn_input(button),
    .btn_output(btn_level)
  );

  LCD_module lcd0( 
    .clk(clk),
    .reset(reset),
    .row_A(row_A),
    .row_B(row_B),
    .LCD_E(LCD_E),
    .LCD_RS(LCD_RS),
    .LCD_RW(LCD_RW),
    .LCD_D(LCD_D)
  );

  Rotation_direction RTD(
    .CLK(clk),
    .ROT_A(ROT_A),
    .ROT_B(ROT_B),
    .rotary_event(rot_event),
    .rotary_right(rot_right)
  );

  // ------------------------------------------------------------------------
  // The following code detects the positive edge of the button-press signal.
  always @(posedge clk) begin
    if (reset) begin
      prev_btn_level <= 1'b1;
    end
    else begin
      prev_btn_level <= btn_level;
    end
  end

  assign btn_pressed = (btn_level == 1 && prev_btn_level == 0)? 1'b1 : 1'b0;
  // End of button-press signal edge detector.
  // ------------------------------------------------------------------------
always @(*)
	begin
		if(counter <= high_ticks) led=8'b11111111;
		else led=8'b00000000;
	end
	
  always @(*)
  begin
	if(!frequency&&duty_cycles==0) high_ticks=100000;//25Hz,5%,100,000 high_ticks
	else if(!frequency&&duty_cycles==1) high_ticks=500000;//25Hz,25%,500000 high_ticks
	else if(!frequency&&duty_cycles==2) high_ticks=1000000;//25Hz,50%,1000000 high_ticks
	else if(!frequency&&duty_cycles==3) high_ticks=1500000;//25Hz,75%,1500000 high_ticks
	else if(!frequency&&duty_cycles==4) high_ticks=2000000;//25Hz,100%,2000000 high_ticks
	else if(frequency&&duty_cycles==0) high_ticks=25000;//100Hz,5%,25000 high_ticks
	else if(frequency&&duty_cycles==1) high_ticks=150000;//100Hz,25%,125000 high_ticks
	else if(frequency&&duty_cycles==2) high_ticks=250000;//100Hz,50%,250000 high_ticks
	else if(frequency&&duty_cycles==3) high_ticks=375000;//100Hz,75%,375000 high_ticks
	else if(frequency&&duty_cycles==4) high_ticks=500000;//100Hz,100%,500000 high_ticks
	else high_ticks=high_ticks;
  end
	
	always@ (posedge clk) begin
    if (reset)
      frequency <= 0;
    else if(btn_pressed)
			frequency <= ~frequency ;
		else
			frequency <= frequency ;
  end
  
	always@(posedge clk) begin
		if(reset)
			counter <= 0 ;
		else if(frequency && counter >= 500000) //100 Hz one cycle has 500000 ticks
			counter <= 0 ;
		else if(!frequency && counter >= 2000000) // 25 Hz one cycle has 2000000 ticks
			counter <= 0 ;
		else
			counter <= counter + 1 ;
	end
	
  always@(posedge clk) begin
		if(reset)
			duty_cycles <= 0 ;
		else if(!rot_right && rot_event && duty_cycles <=3)
			duty_cycles <= duty_cycles + 1 ;
		else if(rot_right && rot_event && duty_cycles >=1 )
			duty_cycles <= duty_cycles - 1 ;
		else
			duty_cycles <= duty_cycles ;
	end
	
  always @(posedge clk) begin
    if (reset) begin
      row_A <= "Frequency:  25Hz";
      row_B <= "Duty cycle:   5%";
    end
    else begin
      if(frequency) row_A[39:16] <= " 100" ;
			else row_A[39:16] <= " 25" ;
			
			if(duty_cycles == 0) row_B[31:8] <= "  5" ;// 2 space
			else if(duty_cycles == 1 ) row_B[31:8] <= " 25" ;// 1space
			else if(duty_cycles == 2 ) row_B[31:8] <= " 50" ;// 1space
			else if(duty_cycles == 3 ) row_B[31:8] <= " 75" ;// 1 space
			else if(duty_cycles == 4 ) row_B[31:8] <= "100" ;// 0 space
    end
  end
  

  
endmodule
