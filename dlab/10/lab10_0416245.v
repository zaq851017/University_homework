`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    14:26:49 12/02/2015 
// Design Name: 
// Module Name:    lab10
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

module lab10(
  input clk,
  input reset,
  output [7:0] led,
  input ROT_A,
  input ROT_B,

  // VGA specific I/O ports
  output VGA_HSYNC,
  output VGA_VSYNC,
  output VGA_RED,
  output VGA_GREEN,
  output VGA_BLUE
  );
  // Declare system variables
  reg [7:0] led_on[0:7];
  wire rot_event;
  wire rot_right;

  // declare SRAM control signals
  reg  [16:0]  sram_addr;
  wire [2:0]  data_in;
  wire [2:0]  data_out;
  reg         we;
  wire        en;

  // General VGA control signals
  wire video_on;      // when video_on is 0, the VGA controller is sending
                      // synchronization signals to the display device.

  wire pixel_tick;    // when pixel tick is 1, we must update the RGB value
                      // based for the new coordinate (pixel_x, pixel_y)

  wire [9:0] pixel_x; // x coordinate of the next pixel (between 0 ~ 639) 
  wire [9:0] pixel_y; // y coordinate of the next pixel (between 0 ~ 479)
  reg [16:0] pixel_addr;
  reg  [2:0] rgb_reg;  // RGB value for the current pixel
  reg  [2:0] rgb_next; // RGB value for the next pixel
  
  // Application-specific VGA signals
  //reg  [16:0] dummy_addr;
  wire [2:0] current_rgb; // RGB values for the frame display application.
                          // In this demo, the value is generated by
                          // a video pattern generator:
                          //      video_pattern(id, x, y, current_rgb),
                          // where the input is the current scan coordinate (x, y),
                          // and the output is the RGB value of the video pattern
                          // 'id' at pixel (x, y).
  reg  [2:0] pattern_id;
  reg  [2:0] moon[111:0];
  reg [2:0] P,P_next;
  localparam [1:0] S_idle = 2'b00, S_rmoon = 2'b01, S_wmoon = 2'b10, S_finish = 2'b11;
  reg  [20:0] rmoon_addr,wmoon_addr;
  reg  [10:0] rcounter,wcounter;
  // Declare the video buffer size
  localparam VBUF_W = 640/2; // video buffer width
  localparam VBUF_H = 480/2; // video buffer height
  reg  [6:0] row;

  // Instiantiate a VGA sync signal generator
  vga_sync vs0(
    .clk(clk), .reset(reset), .oHS(VGA_HSYNC), .oVS(VGA_VSYNC),
    .visible(video_on), .p_tick(pixel_tick),
    .pixel_x(pixel_x), .pixel_y(pixel_y)
  );

  // Instiantiate a rotary dial controller
  Rotation_direction RTD(
    .CLK(clk),
    .ROT_A(ROT_A),
    .ROT_B(ROT_B),
    .rotary_event(rot_event),
    .rotary_right(rot_right)
  );

  // Instiantiate a video test pattern generator
  video_pattern vp0(
    .id(pattern_id),
    .x(pixel_x),
    .y(pixel_y),
    .rgb(current_rgb)
  );

  assign led = { data_out, 2'b0,  pattern_id}; // put data_out here to keep sram from being removed.

  // ------------------------------------------------------------------------
  // The following code describes an initialized SRAM memory block that
  // stores an 320x240 3-bit city image, plus a 112x40 moon image.
  sram #(.DATA_WIDTH(3), .ADDR_WIDTH(17), .RAM_SIZE(VBUF_W*VBUF_H+112*40))
    ram0 (.clk(clk), .we(we), .en(en),
            .addr(sram_addr), .data_i(data_in), .data_o(data_out));

  always @(*)begin
  if (P_next==S_wmoon) we<= 1;
  else we <= 0;
  end
  assign en = 1; // Always enable the SRAM block.
  always @(*)begin
  if(P_next==S_rmoon) sram_addr<=rmoon_addr;
  else if(P_next==S_wmoon)sram_addr<=wmoon_addr;
  else sram_addr<=pixel_addr;
  end
  // End of the SRAM memory block.
  // ------------------------------------------------------------------------
  // VGA color pixel generator
  always @(posedge clk) begin
	if (pixel_tick) rgb_reg <= rgb_next;
  end
  assign {VGA_RED, VGA_GREEN, VGA_BLUE} = rgb_reg;

  // ------------------------------------------------------------------------
// ------------------------------------------------------------------------
  // Use the rotary to control the moon
  always@ (posedge clk) begin
    if (reset)
      pattern_id <= 0;
    else if (rot_event && rot_right && pattern_id<=6)
      pattern_id <= pattern_id + 1;
    else if (rot_event && !rot_right && pattern_id>=1)
      pattern_id <= pattern_id - 1;
  end
  // ------------------------------------------------------------------------
// ----------------------------------------------------------------------
always @ (posedge clk) begin
if(reset||P_next==S_idle) begin
	rcounter<=0;
	wcounter <=0;
	end
else if(P_next==S_rmoon)begin
	rcounter<=rcounter+1;
	end
else if(P_next==S_wmoon)
	wcounter <=wcounter+1;
end

always @ (posedge clk) begin
if(reset)begin
	rmoon_addr<=0;
	wmoon_addr<=0;
end
else if(P_next==S_rmoon) 
	rmoon_addr<=(320*240)+rcounter+(row*112);
else if(P_next==S_wmoon) 
	wmoon_addr<=8*320+(pattern_id*32)+wcounter+(row*320);
end


assign data_in = (P_next==S_wmoon)?moon[wcounter]:0; // SRAM is read-only so we tie inputs to zeros.
always @(posedge clk)begin
if(P_next==S_rmoon)
	moon[rcounter] <= data_out;
end
//---------------------------------------------------------

//---------------------------------------------------------------------------
always@ (posedge clk) begin
if(reset||row>=40)
	row<=0;
else if((P==S_wmoon)&&(wcounter==112))
	row<=row+1;
end
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
always @ (posedge clk) begin
if (reset)
pixel_addr <= 0;
else
// Scale up a 320x240 image for the 640x480 display.
// (pixel_x, pixel_y) ranges from (0,0) to (639, 379)
pixel_addr <= (pixel_y >> 1) * 320 + (pixel_x >> 1);
end
// ------------------ RGB register ----------------------- 
always @(*) begin
if (~video_on)
rgb_next = 3'b000; // Sync period, must set rgb to zeros
else
rgb_next = data_out; // RGB value at (pixel_x, pixel_y)
end
// State Machine------------------------------------------
always @(posedge clk) begin
    if(reset) 
        P=S_idle;
    else
        P=P_next;
end
always @(*) begin
    case(P)
    S_idle: if(video_on) P_next = S_idle;
            else P_next = S_rmoon;
    S_rmoon: if(rcounter>=112) P_next = S_wmoon;
			else P_next = S_rmoon;
    S_wmoon: if(wcounter>=112) P_next= S_finish;
            else P_next = S_wmoon;
	S_finish: if(video_on) P_next = S_idle;
            else P_next = S_finish;
	default : P_next = S_idle;
    endcase
//---------------------------------------------------------
end

endmodule