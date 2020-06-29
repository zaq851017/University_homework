`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    16:30:47 11/22/2015 
// Design Name: 
// Module Name:    lcd 
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
module lab7(
    input clk,
    input reset,
    input  button,
    output LCD_E,
    output LCD_RS,
    output LCD_RW,
    output [3:0]LCD_D
    );
	 
    wire btn_level, btn_pressed;
	 reg OK_Fibo ;   //determined if all fibo number writed in sram
	 wire updataed_lcd ; //determined if updata LCD
	 reg scroll ; // 0  up , 1 down
	 reg prv_scroll ; //previous scroll direction
    reg prev_btn_level ;
	reg prv1_updataed_lcd ,has_updataed_lcd ;//prv1 and prv2 's next_en
    reg [130:0] row_A, row_B;
    reg [24:0] counter ;
	 reg [4:0]  sram_counter ;
	 wire [4:0] fibo_addr ; //the address of Fibo number indicated on LCD
	 // declare a SRAM memory block
	wire [20:0] data_in;
	reg [20:0] data_out;
     reg [20:0]prv_data_o ;
	wire       we, en;
	wire [4:0] sram_addr;
	assign updataed_lcd = &counter ;
	assign en = 1 ;
	assign we = !OK_Fibo ;
  always@(posedge clk) begin
		if(reset) prv_data_o <= 0 ;
		else prv_data_o <= data_out ;
	end
	assign data_in = (sram_addr == 0) ? 0 :  (sram_addr == 1) ? 1 : prv_data_o + data_out ; 
    assign sram_addr = sram_counter ;
	assign fibo_addr = sram_addr + 1 ;
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
    
    debounce btn_db0(
      .clk(clk),
      .btn_input(button),
      .btn_output(btn_level)
   );
   

// Declareation of the memory cells
reg [15 : 0] RAM [511:0];

// ------------------------------------
// SRAM read operation
// ------------------------------------
always@(posedge clk)
begin
  if (en & we)
    data_out <= data_in;
  else
    data_out <= RAM[sram_addr];
end

// ------------------------------------
// SRAM write operation
// ------------------------------------
always@(posedge clk)
begin
  if (en & we)
    RAM[sram_addr] <= data_in;
end


   
	always @(posedge clk) begin
      if (reset)
        prev_btn_level <= 1;
      else
        prev_btn_level <= btn_level;
    end

    assign btn_pressed = (btn_level == 1 && prev_btn_level == 0)? 1 : 0;

    reg in1,in2;
    always @(posedge clk) begin
      if (reset)
        in1 <= 1;
      else
        in2 <= in1;
    end
    
    reg in3;
    always @(posedge clk) begin
      if (reset)
        in3<=0;
      else
        in3<=in3+1;
    end
    
    

	 always @(posedge clk) begin
      if (reset) begin
        row_A <= "Fibo #01 is 0000" ;
        row_B <= "Fibo #02 is 0001";
      end
		else if(!scroll && has_updataed_lcd) begin
			    row_A <= row_B ;
				row_B[15*8 + 7: 10*8 ] <= "Fibo #" ;
				row_B[9*8 + 7 : 9*8] <= fibo_addr[4] + "0"  ;
				row_B[8*8 + 7 : 8*8] <= ((fibo_addr[3:0] > 9 ) ? "7" : "0" ) + fibo_addr[3:0] ;
				row_B[7*8 + 7 : 4*8] <= " is " ;
				row_B[3*8 + 7 : 3*8] <= ((data_out[15:12] > 9 ) ? "7" : "0" ) + data_out[15:12] ;
				row_B[2*8 + 7 : 2*8] <= ((data_out[11:8] > 9 ) ? "7" : "0" ) + data_out[11:8] ;
				row_B[1*8 + 7 : 1*8] <= ((data_out[7:4] > 9 ) ? "7" : "0" ) + data_out[7:4] ;
				row_B[0*8 + 7 : 0*8] <= ((data_out[3:0] > 9 ) ? "7" : "0" ) + data_out[3:0] ;	  
		end
		else if(scroll && has_updataed_lcd) begin
				row_B <= row_A ;
				row_A[15*8 + 7: 10*8 ] <= "Fibo #" ;
				row_A[9*8 + 7 : 9*8] <= fibo_addr[4] + "0"  ;
				row_A[8*8 + 7 : 8*8] <= ((fibo_addr[3:0] > 9 ) ? "7" : "0" ) + fibo_addr[3:0] ;
				row_A[7*8 + 7 : 4*8] <= " is " ;
				row_A[3*8 + 7 : 3*8] <= ((data_out[15:12] > 9 ) ? "7" : "0" ) + data_out[15:12] ;
				row_A[2*8 + 7 : 2*8] <= ((data_out[11:8] > 9 ) ? "7" : "0" ) + data_out[11:8] ;
				row_A[1*8 + 7 : 1*8] <= ((data_out[7:4] > 9 ) ? "7" : "0" ) + data_out[7:4] ;
				row_A[0*8 + 7 : 0*8] <= ((data_out[3:0] > 9 ) ? "7" : "0" ) + data_out[3:0] ;		 
		end
		else begin
			row_A <= row_A ;
			row_B <= row_B ;
		end
    end
	//counter to wait 0.625s between update the screen 
	always @(posedge clk)	begin
		if(reset)begin
			counter <= 0 ;
			OK_Fibo <= 0 ;
		end
		else begin
			counter <= counter + 1 ;
			if(counter >= 24) OK_Fibo <= 1 ;
			else 	OK_Fibo <= OK_Fibo ;			
		end
	end
	//counter to sram_addr , circle every 25 clk  when writing , circle every LCD indicate 25th numnber when reading  
	always @(posedge clk) begin
		if(reset) begin
			sram_counter <= 0 ;
		end
		else if (!OK_Fibo)begin
			sram_counter <= (sram_counter < 24) ? sram_counter + 1 : 1 ;
		end
		else begin
			if(updataed_lcd && !scroll && !prv_scroll) sram_counter <= (sram_counter < 24) ? sram_counter + 1 : 0 ;
			else if(updataed_lcd && !scroll && prv_scroll) sram_counter <= (sram_counter < 23 ) ? sram_counter + 2 : sram_counter - 23  ;
			else if(updataed_lcd && scroll && prv_scroll) sram_counter <= (sram_counter > 0 ) ? sram_counter - 1 : 24 ; 
			else if(updataed_lcd && scroll && !prv_scroll) sram_counter <= (sram_counter > 1 ) ? sram_counter - 2 : sram_counter + 23  ;
			else sram_counter <= sram_counter ; 
		end
	end
	
	
	always@(posedge clk ) begin
		if(reset) scroll <= 0 ;
		else if(btn_pressed ) scroll <= !scroll ;
		else scroll <= scroll ;
	end
	
	always@(posedge clk)begin
		if(reset) begin
		has_updataed_lcd <= 0 ;
		prv1_updataed_lcd <= 0 ;
		end
		else begin 
		prv1_updataed_lcd <= updataed_lcd ;
		has_updataed_lcd <= prv1_updataed_lcd ;
		end
	end
	always@(posedge clk) begin
		if(reset) prv_scroll <= 0 ;
		else if (updataed_lcd) prv_scroll <= scroll ;
		else prv_scroll <= prv_scroll ;
	end
endmodule
