`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: National Chiao Tung University
// Engineer: Chun-Jen Tsai
// 
// Create Date:    15:45:54 10/04/2016 
// Design Name: 
// Module Name:    lab5 
// Project Name: 
// Target Devices: 
// Tool versions: 
// Description: This is a sample top module of lab 5: sd card reader.
//              The behavior of this module is as follows:
//              1. The moudle will read one block (512 bytes) of the SD card
//                 into an on-chip SRAM every time the user hit the WEST button.
//              2. The starting address of the disk block is #8192 (i.e., 0x2000).
//              3. A message will be printed on the UART about the block id and the
//                 first byte of the block.
//              4. After printing the message, the block address will be incremented
//                 by one, waiting for the next user button press.
//
// Dependencies: 
//
// Revision: 
// Revision 0.01 - File Created
// Additional Comments: 
//////////////////////////////////////////////////////////////////////////////////
module lab5(
    // General system I/O ports
    input  clk,
    input  reset,
    input  button,
    input  rx,
    output tx,
    output [7:0] led,

    // SD card specific I/O ports
    output cs,
    output sclk,
    output mosi,
    input  miso
    );

localparam [2:0] S_MAIN_INIT = 0, S_MAIN_IDLE = 1, S_MAIN_MSG1 = 2,
                 S_MAIN_READ = 3, S_MAIN_LOOP = 4, S_MAIN_HEX2TXT = 5,
                 S_MAIN_MSG2 = 6, S_MAIN_DONE = 7;
localparam [1:0] S_UART_IDLE = 0, S_UART_WAIT = 1,
                 S_UART_SEND = 2, S_UART_INCR = 3;
localparam MEM_SIZE = 86;
localparam MESSAGE_STR = 0;
localparam NUMBER_STR = 17;

// declare system variables
wire btn_level, btn_pressed;
reg  prev_btn_level;
reg  print_enable, print_done;
reg  [6:0] send_counter;   
reg  [2:0] P, P_next;
reg  [1:0] Q, Q_next;
reg  [9:0] sd_counter;
reg  [7:0] byte0;
reg  [0:(MEM_SIZE-1)*8+7] data;
reg  [31:0] blk_addr;
reg  [2:0] TAG_counter;
reg  [6:0] data_idx;
reg  TAG_found; 
reg  TAG_not_found;
reg  MATRIX_READY;

// declare UART signals
wire transmit;
wire received;
wire [7:0] rx_byte;
wire [7:0] tx_byte;
wire is_receiving;
wire is_transmitting;
wire recv_error;

// declare SD card interface signals
wire clk_sel;
wire clk_500k;
reg  rd_req;
reg  [31:0] rd_addr;
wire init_finish;
wire [7:0] sd_dout;
wire sd_valid;

// declare a SRAM memory block
wire [7:0] data_in;
wire [7:0] data_out;
wire       we, en;
wire [8:0] sram_addr;

assign clk_sel = (init_finish)? clk : clk_500k; // clocks for the SD controller
assign led = {TAG_found,4'b0,P};//Debug要用的

debounce btn_db0(
  .clk(clk),
  .btn_input(button),
  .btn_output(btn_level));

uart uart0(
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
  .recv_error(recv_error));

sd_card sd_card0(
  .cs(cs),
  .sclk(sclk),
  .mosi(mosi),
  .miso(miso),

  .clk(clk_sel),
  .rst(reset),
  .rd_req(rd_req),
  .block_addr(rd_addr),
  .init_finish(init_finish),
  .dout(sd_dout),
  .sd_valid(sd_valid));

clk_divider#(100) clk_divider0(
  .clk(clk),
  .rst(reset),
  .clk_out(clk_500k));

// Text messages configuration circuit.
always @(posedge clk) 
	begin
		if (reset)
			begin
				data[0   :13*8+7] <= "The matrix is:";
				data[14*8:14*8+7] <= 8'h0D ;
				data[15*8:15*8+7] <= 8'h0A ;
				data[16*8:16*8+7] <= 8'h00 ;
				data[17*8:36*8+7] <= "[ 0000, 0000, 0000 ]";
				data[37*8:37*8+7] <= 8'h0D ;
				data[38*8:38*8+7] <= 8'h0A ;
				data[39*8:58*8+7] <= "[ 0000, 0000, 0000 ]";
				data[59*8:59*8+7] <= 8'h0D ;
				data[60*8:60*8+7] <= 8'h0A ;
				data[61*8:80*8+7] <= "[ 0000, 0000, 0000 ]";
				data[81*8:81*8+7] <= 8'h0D ;
				data[82*8:82*8+7] <= 8'h0A ;
				data[83*8:83*8+7] <= 8'h0D ;
				data[84*8:84*8+7] <= 8'h0A ;
				data[85*8:85*8+7] <= 8'h00 ;
				TAG_counter <= 0;
				TAG_found <= 0;
				TAG_not_found <= 0;
				MATRIX_READY <= 0;
				data_idx = 0;
			end
			
		else
			begin
			if(P == S_MAIN_MSG1) 
				begin 
					TAG_found <= 0; 
					data_idx  = 0; 
					MATRIX_READY <= 0; 
				end
			if(P == S_MAIN_READ) 
				TAG_not_found <= 0;
			if(P == S_MAIN_MSG2 && !TAG_found) 
				begin
					case (TAG_counter) // finding the TAG
						0:if(byte0[7:0]=="D")
							TAG_counter <= TAG_counter + 1;		
						  else 
								begin 
									TAG_not_found <= 1; 
									TAG_counter <= 0;
								end
						1:if(byte0[7:0]=="L") 
							TAG_counter <= TAG_counter + 1;		
						  else 
							begin 
									TAG_not_found <= 1; 
									TAG_counter <= 0; 
								end
						2:if(byte0[7:0]=="A") 
							TAG_counter <= TAG_counter + 1;		
						  else 
							begin 
								TAG_not_found <= 1; 
								TAG_counter <= 0; 
							end
						3:if(byte0[7:0]=="B")
							TAG_counter <= TAG_counter + 1;		
						  else 
							begin 
								TAG_not_found <= 1; 
								TAG_counter <= 0; 
							end
						4:if(byte0[7:0]=="_") 
							TAG_counter <= TAG_counter + 1;		
						  else 
							begin 
								TAG_not_found <= 1; 
								TAG_counter <= 0;
							end
						5:if(byte0[7:0]=="T")
							TAG_counter <= TAG_counter + 1;		
						  else
							begin 
								TAG_not_found <= 1; 
								TAG_counter <= 0;
							end
						6:if(byte0[7:0]=="A")
							TAG_counter <= TAG_counter + 1;		
						  else 
							begin 
								TAG_not_found <= 1;
								TAG_counter <= 0; 
							end
						7:if(byte0[7:0]=="G")
							TAG_found <= 1;										
						  else 
								begin 
									TAG_not_found <= 1; 
									TAG_counter <= 0;
								end
					endcase
				end
			if(P == S_MAIN_MSG2 && TAG_found)   
				begin //i的變動順著sd_counter的變動，不然進來的byte0會對不到
					case (data_idx)//0D,0A先進來   EX:19*8+:8=19*8:19*8+7
					//1-1
			2:data[19*8:19*8+7] <= byte0[7:0]; 3:data[20*8:20*8+7] <= byte0[7:0]; 4:data[21*8:21*8+7] <= byte0[7:0]; 5:data[22*8:22*8+7] <= byte0[7:0];
			//2-1
			8:data[41*8:41*8+7] <= byte0[7:0]; 9:data[42*8:42*8+7] <= byte0[7:0]; 10:data[43*8:43*8+7] <= byte0[7:0]; 11:data[44*8:44*8+7] <= byte0[7:0]; 
			//3-1
			14:data[63*8:63*8+7] <= byte0[7:0]; 15:data[64*8:64*8+7] <= byte0[7:0]; 16:data[65*8:65*8+7] <= byte0[7:0]; 17:data[66*8:66*8+7] <= byte0[7:0];
			//1-2
			20:data[25*8:25*8+7] <= byte0[7:0]; 21:data[26*8:26*8+7] <= byte0[7:0]; 22:data[27*8:27*8+7] <= byte0[7:0]; 23:data[28*8:28*8+7] <= byte0[7:0]; 
			//2-2
			26:data[47*8:47*8+7] <= byte0[7:0]; 27:data[48*8:48*8+7] <= byte0[7:0]; 28:data[49*8:49*8+7] <= byte0[7:0]; 29:data[50*8:50*8+7] <= byte0[7:0]; 
			//3-2
			32:data[69*8:69*8+7] <= byte0[7:0]; 33:data[70*8:70*8+7] <= byte0[7:0]; 34:data[71*8:71*8+7] <= byte0[7:0]; 35:data[72*8:72*8+7] <= byte0[7:0];
			//1-3
			38:data[31*8:31*8+7] <= byte0[7:0]; 39:data[32*8:32*8+7] <= byte0[7:0]; 40:data[33*8:33*8+7] <= byte0[7:0]; 41:data[34*8:34*8+7] <= byte0[7:0]; 
			//2-3
			44:data[53*8:53*8+7] <= byte0[7:0]; 45:data[54*8:54*8+7] <= byte0[7:0]; 46:data[55*8:55*8+7] <= byte0[7:0]; 47:data[56*8:56*8+7] <= byte0[7:0]; 
			//3-3
			50:data[75*8:75*8+7] <= byte0[7:0]; 51:data[76*8:76*8+7] <= byte0[7:0]; 52:data[77*8:77*8+7] <= byte0[7:0]; 53:begin data[78*8:78*8+7] <= byte0[7:0]; MATRIX_READY <= 1; end 
						/*2:data[19*8+:8]<=byte0[7:0];   3:data[20*8+:8]<=byte0[7:0];  4:data[21*8+:8]<=byte0[7:0];  5:data[22*8+:8]<=byte0[7:0];      24:data[25*8+:8]<=byte0[7:0];  25:data[26*8+:8]<=byte0[7:0]; 26:data[27*8+:8]<=byte0[7:0]; 27:data[28*8+:8]<=byte0[7:0];    46:data[31*8+:8]<=byte0[7:0]; 47:data[32*8+:8]<=byte0[7:0]; 48:data[33*8+:8]<=byte0[7:0]; 49:data[34*8+:8]<=byte0[7:0];
						8:data[41*8+:8]<=byte0[7:0];   9:data[42*8+:8]<=byte0[7:0]; 10:data[43*8+:8]<=byte0[7:0]; 11:data[44*8+:8]<=byte0[7:0];      30:data[47*8+:8]<=byte0[7:0];  31:data[48*8+:8]<=byte0[7:0]; 32:data[49*8+:8]<=byte0[7:0]; 33:data[50*8+:8]<=byte0[7:0];    52:data[53*8+:8]<=byte0[7:0]; 53:data[54*8+:8]<=byte0[7:0]; 54:data[55*8+:8]<=byte0[7:0]; 55:data[56*8+:8]<=byte0[7:0];
						14:data[63*8+:8]<=byte0[7:0]; 15:data[64*8+:8]<=byte0[7:0]; 16:data[65*8+:8]<=byte0[7:0]; 17:begin data[66*8+:8]<=byte0[7:0]; i = i + 4; end    36:data[69*8+:8]<=byte0[7:0]; 37:data[70*8+:8]<=byte0[7:0]; 38:data[71*8+:8]<=byte0[7:0]; 39:begin data[72*8+:8]<=byte0[7:0]; i = i + 4; end 58:data[75*8+:8]<=byte0[7:0]; 59:data[76*8+:8]<=byte0[7:0]; 60:data[77*8+:8]<=byte0[7:0]; 61:begin data[78*8+:8]<=byte0[7:0]; MATRIX_READY <= 1; end*/
					//2,3,4,5 8,9,10,11 14,15,16,17
					//24,27   30,33     36,39
					//46,49   52,55     58,61
					endcase
					data_idx = data_idx + 1;
				end
			end
	end

// Enable one cycle of btn_pressed per each button hit.
assign btn_pressed = (btn_level == 1 && prev_btn_level == 0)? 1 : 0;

always @(posedge clk) begin
  if (reset)
    prev_btn_level <= 0;
  else
    prev_btn_level <= btn_level;
end

// ------------------------------------------------------------------------
// The following code describes an SRAM memory block that is connected
// to the data output port of the SD controller.
// Once the read request is made to the SD controller, 512 bytes of data
// will be sequentially read into the SRAM memory block, one byte per
// clock cycle (as long as the sd_valid signal is high).
sram ram0(.clk(clk), .we(we), .en(en),
          .addr(sram_addr), .data_i(data_in), .data_o(data_out));

assign we = sd_valid;     // Write data into SRAM when sd_valid is high.
assign en = 1;             // Always enable the SRAM block.
assign data_in = sd_dout;  // Input data always comes from the SD controller.

// Set the driver of the SRAM address signal.
assign sram_addr = sd_counter[8:0];

always @(posedge clk)
	begin // Controller of the 'sd_counter' signal.
		if (reset || P == S_MAIN_READ) 
			sd_counter <= 0;
		else if (P == S_MAIN_LOOP && sd_valid)  
			sd_counter <= sd_counter + 1;
		else if (P == S_MAIN_HEX2TXT)
			sd_counter <= sd_counter + 1;
	end

always @(posedge clk)
	begin // Stores sram[0] in the register 'byte0'.
		if (reset) byte0 <= 8'b0;
		else if (en && P == S_MAIN_HEX2TXT) byte0 <= data_out;
	end
//
// End of the SRAM memory block
// ------------------------------------------------------------------------

// ------------------------------------------------------------------------
// FSM of the main circuit that reads a SD card sector (512 bytes)
// and then print its byte.
//
always @(posedge clk)
	begin 
		if (reset) P <= S_MAIN_INIT;
		else P <= P_next;
	end

always @(*)
	begin // FSM next-state logic
		case (P)
			S_MAIN_INIT: // wait for SD card initialization
				if (init_finish) P_next = S_MAIN_IDLE;
				else P_next = S_MAIN_INIT;
			
			S_MAIN_IDLE: // 等按按鈕
				if (btn_pressed == 1) P_next = S_MAIN_MSG1;
				else P_next = S_MAIN_IDLE;
			
			S_MAIN_MSG1: // 輸出 The matrix is : 
				if (print_done) P_next = S_MAIN_READ;
				else P_next = S_MAIN_MSG1;
//---------------這邊以上的FSM沒問題-------------------------

			S_MAIN_READ: // 要data，重置以下步驟裡的變數
				P_next = S_MAIN_LOOP;
			
			S_MAIN_LOOP: // 存data 
				if (sd_counter == 512) P_next = S_MAIN_HEX2TXT;
				else P_next = S_MAIN_LOOP;
			
			S_MAIN_HEX2TXT: // 緩衝，用byte0接data_out，重置MSG2裡的變數 ，讓byte0 <= data_out
				P_next = S_MAIN_MSG2;
			
			S_MAIN_MSG2: // 讀byte0，找DLAB_TAG，並儲存DLAB_TAG後的資料
				if (MATRIX_READY) P_next = S_MAIN_DONE;
				else if(TAG_not_found) P_next = S_MAIN_READ;
				else P_next = S_MAIN_HEX2TXT;
			
			S_MAIN_DONE: // 輸出結果 
				if (print_done) P_next = S_MAIN_IDLE;
				else P_next = S_MAIN_DONE;
		endcase
	end

// FSM output logics: print string control signals.
always @(*)
	begin
		if ((P == S_MAIN_IDLE && btn_pressed == 1) || (P == S_MAIN_MSG2 && TAG_found))
			print_enable = 1;
		else
			print_enable = 0;
	end

// FSM output logic: controls the 'rd_req' and 'rd_addr' signals.
always @(*)
	begin
		rd_req = (P == S_MAIN_READ);
		rd_addr = blk_addr;
	end

// SD card read address incrementer
always @(posedge clk)
	begin
		if (reset || btn_pressed || P == S_MAIN_IDLE) blk_addr <= 32'h2000;  //讓它重新回位置2000
		else
			begin
				blk_addr <= blk_addr + (P == S_MAIN_MSG2 &&  TAG_not_found); 
				if(blk_addr == 7736319 || blk_addr > 7736319) blk_addr <= 8192;
			end
	end
//
// End of the FSM of the SD card reader
// ------------------------------------------------------------------------

// -----以下盡量不改-------------------------------------------------------------------
// FSM of the controller to send a string to the UART.
//
always @(posedge clk) begin
  if (reset) Q <= S_UART_IDLE;
  else Q <= Q_next;
end

always @(*) begin // FSM next-state logic
  case (Q)
    S_UART_IDLE: // wait for print_string flag
      if (print_enable) Q_next = S_UART_WAIT;
      else Q_next = S_UART_IDLE;
    S_UART_WAIT: // wait for the transmission of current data byte begins
      if (is_transmitting == 1) Q_next = S_UART_SEND;
      else Q_next = S_UART_WAIT;
    S_UART_SEND: // wait for the transmission of current data byte finishes
      if (is_transmitting == 0) Q_next = S_UART_INCR; // transmit next character
      else Q_next = S_UART_SEND;
    S_UART_INCR:
      if (tx_byte == 8'h0) Q_next = S_UART_IDLE; // string transmission ends
      else Q_next = S_UART_WAIT;
  endcase
end

// FSM output logics
assign transmit = (Q == S_UART_WAIT)? 1 : 0;
assign tx_byte = data[{ send_counter, 3'b000 } +: 8];

// Send_counter incrementing circuit.
always @(posedge clk) begin
  if (reset) begin
    send_counter <= MESSAGE_STR;
    print_done <= 0;
  end
  else begin
    if (P == S_MAIN_IDLE)
      send_counter <= MESSAGE_STR;
    else if (P == S_MAIN_MSG2) 
      send_counter <= NUMBER_STR;
    else
      send_counter <= send_counter + (Q == S_UART_SEND && Q_next == S_UART_INCR);
      print_done <= (print_enable)? 0 : (tx_byte == 8'h0);
  end
end
//
// End of the FSM of the print string controller
// ------------------------------------------------------------------------

endmodule