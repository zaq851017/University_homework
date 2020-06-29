`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: National Chiao Tung University
// Engineer: Chun-Jen Tsai
// 
// Create Date:    11:26:45 11/23/2016 
// Design Name: 
// Module Name:    lab8 
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
module lab8(
  input clk,
  input reset,
  input button,
  output [7:0] led,
  output LCD_E,
  output LCD_RS,
  output LCD_RW,
  output [3:0] LCD_D
  );

  // declare system variables
  wire btn_level, btn_pressed;
  reg prev_btn_level;
  reg [127:0] row_A, row_B;
  reg [127:0] pixel_addr_msg;
  reg [127:0] pixel_data_msg;
  reg [15:0]  pixel_addr;//deal with pixel_address
  reg [7:0]   pixel_data;//deal with pixel_value

  // declare SRAM control signals
  wire [13:0] sram_addr;
  wire [7:0]  data_in;
  wire [7:0]  data_out;
  wire        we, en;

  //declare shift register
  reg [10:0] shifter [4:0] ;
  reg [15:0] edge_counter ;
  reg [15:0] counter1;
  reg [15:0] counter2;
  wire counter3;
  wire en_add ;
  wire out_finished;
  wire if_edge ;
  wire signed [10:0]sum  ;
  wire [10:0]abs_sum ; 
  wire signed [3:0]g[4:0] ;
  assign g[0] = -1 ;
  assign g[1] = -2 ;
  assign g[2] = 0 ;
  assign g[3] = 2 ;
  assign g[4] = 1 ;
   
  assign sum = (en_add)? (shifter[4] * g[0] + shifter[3] * g[1] + shifter[2] * g[2] + shifter[1] * g[3] + shifter[0] * g[4]) : 0 ; 
  assign out_finished = (pixel_addr >= 160 * 89 + 4  ) ? 1 : 0 ;
  assign en_add = (pixel_addr >= 165 ) ? 1 : 0 ;  
  assign abs_sum = (sum <=0) ? (-1)*sum : sum ;
  assign if_edge = (abs_sum > 200) ? 1 : 0 ;
  assign led = pixel_data;
 
always @(posedge clk)
begin if(reset)
	begin
	counter1 <=0;
	counter2 <=0;
	end
	 else
	 begin
	 counter1<=counter1+1;
	 counter2<=(counter2)+2;
	 end
end	 
assign counter3=(counter2>=counter1)?1:0;

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

  // ------------------------------------------------------------------------
  // The following code describes an initialized SRAM memory block that
  // stores an 160x90 8-bit graylevel image.
  sram ram0(.clk(clk), .we(we), .en(en),
            .addr(sram_addr), .data_i(data_in), .data_o(data_out));

  assign we = 0; // Make the SRAM read-only.
  assign en = 1; // Always enable the SRAM block.
  assign sram_addr = pixel_addr[13:0];
  assign data_in = 8'b0; // SRAM is read-only so we tie inputs to zeros.
  // End of the SRAM memory block.
  // ------------------------------------------------------------------------

  // ------------------------------------------------------------------------
  // The following code updates the 1602 LCD text messages.
  always @(posedge clk) begin
    if (reset) 
      pixel_addr_msg <= "The edge pixel  "; //two space
  end

  always @(posedge clk) begin
    if (reset) begin
      pixel_data_msg <= "  number is XXXX";
    end
    else if(out_finished) begin
      pixel_data_msg[31:24] <= ((edge_counter[15:12] > 9)? "7" : "0") + edge_counter[15:12];
      pixel_data_msg[23:16] <= ((edge_counter[11:8] > 9)? "7" : "0") + edge_counter[11:8];
      pixel_data_msg[15:8] <= ((edge_counter[7:4] > 9)? "7" : "0") + edge_counter[7:4];
      pixel_data_msg[7:0] <= ((edge_counter[3:0] > 9)? "7" : "0") + edge_counter[3:0];
    end
  end
  // End of the 1602 LCD text-updating code.
  // ------------------------------------------------------------------------

  // ------------------------------------------------------------------------
  // The following code detects the positive edge of the button-press signal.
  always @(posedge clk) begin
    if (reset)
      prev_btn_level <= 1'b1;
    else
      prev_btn_level <= btn_level;
  end

  assign btn_pressed = (btn_level == 1 && prev_btn_level == 0)? 1'b1 : 1'b0;
  // End of button-press signal edge detector.
  // ------------------------------------------------------------------------

  // ------------------------------------------------------------------------
  // The main code that processes the user's button event.
  reg data_fetch;
  
  always @(posedge clk) begin
    if (reset) begin
      pixel_addr <= 160;
      data_fetch <= 0;
    end
    else if ((btn_pressed || data_fetch) && !out_finished) begin
      pixel_addr <= pixel_addr + 1;
      data_fetch <= 1;
    end
  end

  always @(posedge clk) begin
    if (reset) begin
      row_A <= "Press WEST to do";
      row_B <= "edge detection..";
      pixel_data <= 8'b0;
    end
    else if (data_fetch) begin
      row_A <= pixel_addr_msg;
      row_B <= pixel_data_msg;
      pixel_data <= data_out;
    end
  end
  // End of the main code.
  // ------------------------------------------------------------------------
always @ (posedge clk) begin
    if(reset) begin
      shifter[0] <= 0 ;
      shifter[1] <= 0 ;
      shifter[2] <= 0 ;
      shifter[3] <= 0 ;
      shifter[4] <= 0 ;
    end
    else begin
      shifter[4] <= data_out ; 
      shifter[3] <= shifter[4] ;
      shifter[2] <= shifter[3] ;
      shifter[1] <= shifter[2] ;
      shifter[0] <= shifter[1] ;
    end
  end
 always@(posedge clk)begin
      if(reset) edge_counter <= 0 ;
      else if(if_edge) edge_counter <= edge_counter + 1 ;
    end
	
endmodule
