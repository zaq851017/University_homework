`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: National Chiao Tung University
// Engineer: Chun-Jen Tsai
// 
// Create Date:    06:30:08 10/03/2016 
// Design Name: 
// Module Name:    lab4 
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
module lab4(
    input clk,
    input reset,
    input rx,
    output tx,
    output [7:0] led
    );

localparam [1:0] S_INIT = 2'b00, S_PROMPT = 2'b01, S_WAIT_KEY = 2'b10, S_HELLO = 2'b11;
localparam [2:0]	S_ECHO=4;
localparam [1:0] S_IDLE = 2'b00, S_WAIT = 2'b01, S_SEND = 2'b10, S_INCR = 2'b11;
localparam MEM_SIZE = 65;
localparam PROMPT_STR = 0;
localparam HELLO_STR = 25;
localparam ECHO_STR = 60;

// declare system variables
wire enter_pressed,key_pressed;
reg [5:0] string_id;
reg print_enable, print_done;
reg [5:0] send_counter;
reg [1:0] P, P_next;
reg [1:0] Q, Q_next;
reg [7:0] data[0:MEM_SIZE-1];
reg [15:0] init_counter;
reg [3:0] hex_counter;
integer idx;

// declare UART signals
wire transmit;
wire received;
wire [7:0] rx_byte;
reg  [7:0] rx_temp;
reg  [18:0] dec;
reg  [7:0] hex[3:0]; 
wire [7:0] tx_byte;
wire is_receiving;
wire is_transmitting;
wire recv_error;

assign enter_pressed  = (rx_temp == 8'h0D);
assign key_pressed = (rx_temp==8'h30)||(rx_temp==8'h31)||(rx_temp==8'h32)||(rx_temp==8'h33)||(rx_temp==8'h34)||(rx_temp==8'h35)||(rx_temp==8'h36)||(rx_temp==8'h37)||(rx_temp==8'h38)||(rx_temp==8'h39);
assign led = { 8'b0 };
assign tx_byte =data[send_counter];

uart uart(
    .clk(clk),
    .rst(reset),
    .rx(rx),
    .tx(tx),
    .transmit(transmit),
    .tx_byte(tx_byte),
    .received(received),
    .rx_byte(rx_byte),
    .is_receiving(is_receiving),
    .is_transmitting(is_transmitting),
    .recv_error(recv_error)
    );

// Initializes some strings.
always @(posedge clk) begin
  if (reset) begin
    data[ 0] <= 8'h45; // E
    data[ 1] <= 8'h6E; // n
    data[ 2] <= 8'h74; // t
    data[ 3] <= 8'h65; // e
    data[ 4] <= 8'h72; // r
    data[ 5] <= 8'h20; // space
    data[ 6] <= 8'h61; // a
    data[ 7] <= 8'h20; // space
    data[ 8] <= 8'h64; // d
    data[ 9] <= 8'h65; // e
    data[10] <= 8'h63; // c
    data[11] <= 8'h69; // i
    data[12] <= 8'h6D; // m
    data[13] <= 8'h61; // a
    data[14] <= 8'h6C; // l
    data[15] <= 8'h20; // space
    data[16] <= 8'h6E; // n
    data[17] <= 8'h75; // u
    data[18] <= 8'h6D; // m
    data[19] <= 8'h62; // b
    data[20] <= 8'h65; // e
    data[21] <= 8'h72; // r
    data[22] <= 8'h3A; // :
	 data[23] <= 8'h20; // space
	 data[24] <= 8'h00;
	 
	 data[25] <= 8'h0D;
	 data[26] <= 8'h0A;
    data[27] <= 8'h54; // T
    data[28] <= 8'h68; // h
    data[29] <= 8'h65; // e
    data[30] <= 8'h20; // space
    data[31] <= 8'h68; // h
    data[32] <= 8'h65; // e
    data[33] <= 8'h78; // x
    data[34] <= 8'h61; // a
    data[35] <= 8'h64; // d
	 data[36] <= 8'h65; // e
	 data[37] <= 8'h63; // c
	 data[38] <= 8'h69; // i
	 data[39] <= 8'h6D; // m
	 data[40] <= 8'h61; // a
	 data[41] <= 8'h6C; // l
	 data[42] <= 8'h20; // space
	 data[43] <= 8'h6E; // n
    data[44] <= 8'h75; // u
    data[45] <= 8'h6D; // m
    data[46] <= 8'h62; // b
    data[47] <= 8'h65; // e
    data[48] <= 8'h72; // r
	 data[49] <= 8'h20; // space
	 data[50] <= 8'h69; // i
	 data[51] <= 8'h73; // s
	 data[52] <= 8'h3A; // :
	 data[53] <= 8'h20; // space
	 data[58] <= 8'h0D;
	 data[59] <= 8'h0A;
	 data[60] <= 8'h00;
  end
  else if(key_pressed||enter_pressed) begin
	 data[54] <=hex[3];
	 data[55] <=hex[2];
	 data[56] <=hex[1];
	 data[57] <=hex[0];
	 data[60] <= rx_temp;
	 data[61] <= 8'h00; 
  end
  else  begin
    for (idx = 0; idx < MEM_SIZE; idx = idx + 1) data[idx] <= data[idx];
  end
end

// ------------------------------------------------------------------------
// Main FSM that reads the UART input and triggers
// the output of the string "Hello, World!".
//
always @(posedge clk) begin
  if (reset) P <= S_INIT;
  else P <= P_next;
end

always @(*) begin // FSM next-state logic
  case (P)
    S_INIT: // wait 1 ms for the UART controller to initialize.
	   if (init_counter < 50000) P_next = S_INIT;
		else P_next = S_PROMPT;
    S_PROMPT: // Print the prompt message.
      if (print_done) P_next = S_WAIT_KEY;
      else P_next = S_PROMPT;
    S_WAIT_KEY: // wait for <Enter> key.
      if (enter_pressed) P_next = S_HELLO;
		else if	(key_pressed) P_next=S_ECHO;
      else P_next = S_WAIT_KEY;
    S_HELLO: // Print the hello message.
      if (send_counter==53) P_next = S_PROMPT;
      else P_next = S_HELLO;
	S_ECHO:
		if(print_done) P_next = S_WAIT_KEY;
		else P_next = S_ECHO;
  endcase
end

// FSM output logics
always @(posedge clk) begin
if(P_next == S_PROMPT)
	string_id =  PROMPT_STR ;
else if(P_next == S_HELLO)
	string_id =HELLO_STR;
else 
	string_id = ECHO_STR;
end



always @(posedge clk) begin
  if (reset) print_enable <= 0;
  else print_enable <= (P_next == S_PROMPT) | (P_next == S_HELLO) |(P_next == S_ECHO);
end

// Initialization counter.
always @(posedge clk) begin
  if (reset) init_counter <= 0;
  else init_counter <= init_counter + 1;
end

//
// End of the FSM of the print string controller
// ------------------------------------------------------------------------

// ------------------------------------------------------------------------
// FSM of the controller to send a string to the UART.
//
always @(posedge clk) begin
  if (reset) Q <= S_IDLE;
  else Q <= Q_next;
end

always @(*) begin // FSM next-state logic
  case (Q)
    S_IDLE: // wait for print_string flag
      if (print_enable) Q_next = S_WAIT;
      else Q_next = S_IDLE;
    S_WAIT: // wait for the transmission of current data byte begins
      if (is_transmitting == 1) Q_next = S_SEND;
      else Q_next = S_WAIT;
    S_SEND: // wait for the transmission of current data byte finishes
      if (is_transmitting == 0) Q_next = S_INCR; // transmit next character
      else Q_next = S_SEND;
    S_INCR:
      if (tx_byte == 8'h0) Q_next = S_IDLE; // string transmission ends
      else Q_next = S_WAIT;
  endcase
end

// FSM output logics
assign transmit = (Q == S_WAIT)? 1 : 0;
//	FSM-controlled echo


// FSM-controlled send_counter incrementing data path
always @(posedge clk) begin
  if (reset)
    send_counter <= 0;
  else if (Q == S_INCR) begin
    // If (tx_byte == 8'h0), it means we hit the end of a string.
    send_counter <= (tx_byte == 8'h0)? string_id : send_counter + 1;
    print_done <= (tx_byte == 8'h0);
  end
  else // 'print_done' and 'print_enable' are mutually exclusive!
    print_done <= ~print_enable;
end
//
// End of the FSM of the print string controller
// ------------------------------------------------------------------------

// ------------------------------------------------------------------------
// The following logic stores the UART input in a temporary buffer.
// The input character will stay in the buffer for one clock cycle.
//
always @(posedge clk) begin
  rx_temp <= (received)? rx_byte : 8'h0;
  
end
// ------------------------------------------------------------------------
always @(negedge clk) begin
	if(enter_pressed)begin
		 for (hex_counter = 0;hex_counter<4; hex_counter = hex_counter + 1)begin  
			case(dec%16)
				0:
				hex[hex_counter]=8'h30;//0
				1:
				hex[hex_counter]=8'h31;//1
				2:
				hex[hex_counter]=8'h32;//2
				3:
				hex[hex_counter]=8'h33;//3
				4:
				hex[hex_counter]=8'h34;//4
				5:
				hex[hex_counter]=8'h35;//5
				6:
				hex[hex_counter]=8'h36;//6
				7:
				hex[hex_counter]=8'h37;//7
				8:
				hex[hex_counter]=8'h38;//8
				9:
				hex[hex_counter]=8'h39;//9
				10:
				hex[hex_counter]=8'h41;//A
				11:
				hex[hex_counter]=8'h42;//B
				12:
				hex[hex_counter]=8'h43;//C
				13:
				hex[hex_counter]=8'h44;//D
				14:
				hex[hex_counter]=8'h45;//E
				15:
				hex[hex_counter]=8'h46;//F
			endcase
			dec=dec/16;
		end
	end
	else if(key_pressed)begin
		dec=dec*10+(rx_temp-8'h30);
		if(dec>65535)
			dec=0;
	end
	
end

 
endmodule
