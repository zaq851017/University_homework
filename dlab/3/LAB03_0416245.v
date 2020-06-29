`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    23:32:15 10/09/2016 
// Design Name: 
// Module Name:    MorseDecoder 
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
module MorseDecoder(
input clk,
input enable,
input  [79:0] in_bits,
output reg [34:0] out_text,
output valid
    );
reg [79:0] in=0;
reg [15:0] dec_reg=0;
reg finish=0;
  /*parameter [15:0] A = 16'b0000000000010111;
	 parameter [15:0] B = 16'b0000000111010101;
	 parameter [15:0] C = 16'b0000011101011101;
	 parameter [15:0] D = 16'b0000000001110101;
	 parameter [15:0] E = 16'b0000000000000001;
	 parameter [15:0] F = 16'b0000000101011101;
	 parameter [15:0] G = 16'b0000000111011101;
	 parameter [15:0] H = 16'b0000000001010101;
	 parameter [15:0] I = 16'b0000000000000101;
	 parameter [15:0] J = 16'b0001011101110111;
	 parameter [15:0] K = 16'b0000000111010111;
	 parameter [15:0] L = 16'b0000000101110101;
	 parameter [15:0] M = 16'b0000000001110111;
	 parameter [15:0] N = 16'b0000000000011101;
	 parameter [15:0] O = 16'b0000011101110111;
	 parameter [15:0] P = 16'b0000010111011101;
	 parameter [15:0] Q = 16'b0001110111010111;
	 parameter [15:0] R = 16'b0000000001011101;
	 parameter [15:0] S = 16'b0000000000010101;
	 parameter [15:0] T = 16'b0000000000000111;
	 parameter [15:0] U = 16'b0000000001010111;
	 parameter [15:0] V = 16'b0000000101010111;
	 parameter [15:0] W = 16'b0000000101110111;
	 parameter [15:0] X = 16'b0000011101010111;
	 parameter [15:0] Y = 16'b0001110101110111;
	 parameter [15:0] Z = 16'b0000011101110101;*/
wire A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z ;
// dec_reg[15] [14] [13] =0 (All)
assign A = !dec_reg[12] && !dec_reg[11] && !dec_reg[10] && !dec_reg[9] && !dec_reg[8] && !dec_reg[7] && !dec_reg[6] && !dec_reg[5] && dec_reg[4] && !dec_reg[3] && dec_reg[2] && dec_reg[1] && !dec_reg[15] && !dec_reg[14] && !dec_reg[13] && dec_reg[0] ;
assign B = !dec_reg[12] && !dec_reg[11] && !dec_reg[10] && !dec_reg[9] && dec_reg[8] && dec_reg[7] && dec_reg[6] && !dec_reg[5] && dec_reg[4] && !dec_reg[3] && dec_reg[2] && !dec_reg[1]&& !dec_reg[15] && !dec_reg[14] && !dec_reg[13] && dec_reg[0] ;
assign C = !dec_reg[12] && !dec_reg[11] && dec_reg[10] && dec_reg[9] && dec_reg[8] && !dec_reg[7] && dec_reg[6] && !dec_reg[5] && dec_reg[4] && dec_reg[3] && dec_reg[2] && !dec_reg[1] && !dec_reg[15] && !dec_reg[14] && !dec_reg[13] && dec_reg[0];
assign D = !dec_reg[12] && !dec_reg[11] && !dec_reg[10] && !dec_reg[9] && !dec_reg[8] && !dec_reg[7] && dec_reg[6] && dec_reg[5] && dec_reg[4] && !dec_reg[3] && !dec_reg[2] && dec_reg[1] && !dec_reg[15] && !dec_reg[14] && !dec_reg[13] && dec_reg[0];
assign E = !dec_reg[12] && !dec_reg[11] && !dec_reg[10] && !dec_reg[9] && !dec_reg[8] && !dec_reg[7] && !dec_reg[6] && !dec_reg[5] && !dec_reg[4] && !dec_reg[3] && !dec_reg[2] && !dec_reg[1] && !dec_reg[15] && !dec_reg[14] && !dec_reg[13] && dec_reg[0];
assign F = !dec_reg[12] && !dec_reg[11] && !dec_reg[10] && !dec_reg[9] && dec_reg[8] && !dec_reg[7] && dec_reg[6] && !dec_reg[5] && dec_reg[4] && dec_reg[3] && dec_reg[2] && !dec_reg[1] && !dec_reg[15] && !dec_reg[14] && !dec_reg[13] && dec_reg[0];
assign G = !dec_reg[12] && !dec_reg[11] && !dec_reg[10] && !dec_reg[9] && dec_reg[8] && dec_reg[7] && dec_reg[6] && !dec_reg[5] && dec_reg[4] && dec_reg[3] && dec_reg[2] && !dec_reg[1] && !dec_reg[15] && !dec_reg[14] && !dec_reg[13] && dec_reg[0];
assign H = !dec_reg[12] && !dec_reg[11] && !dec_reg[10] && !dec_reg[9] && !dec_reg[8] && !dec_reg[7] && dec_reg[6] && !dec_reg[5] && dec_reg[4] && !dec_reg[3] && dec_reg[2] && !dec_reg[1] && !dec_reg[15] && !dec_reg[14] && !dec_reg[13] && dec_reg[0];
assign I =!dec_reg[12] && !dec_reg[11] && !dec_reg[10] && !dec_reg[9] && !dec_reg[8] && !dec_reg[7] && !dec_reg[6] && !dec_reg[5] && !dec_reg[4] && !dec_reg[3] && dec_reg[2] && !dec_reg[1] && !dec_reg[15] && !dec_reg[14] && !dec_reg[13] && dec_reg[0];
assign J = dec_reg[12] && !dec_reg[11] && dec_reg[10] && dec_reg[9] && dec_reg[8] && !dec_reg[7] && dec_reg[6] && dec_reg[5] && dec_reg[4] && !dec_reg[3] && dec_reg[2] && dec_reg[1] && !dec_reg[15] && !dec_reg[14] && !dec_reg[13] && dec_reg[0];
assign K =!dec_reg[12] && !dec_reg[11] && !dec_reg[10] && !dec_reg[9] && dec_reg[8] && dec_reg[7] && dec_reg[6] && !dec_reg[5] && dec_reg[4] && !dec_reg[3] && dec_reg[2] && dec_reg[1] && !dec_reg[15] && !dec_reg[14] && !dec_reg[13] && dec_reg[0];
assign L = !dec_reg[12] && !dec_reg[11] && !dec_reg[10] && !dec_reg[9] && dec_reg[8] && !dec_reg[7] && dec_reg[6] && dec_reg[5] && dec_reg[4] && !dec_reg[3] && dec_reg[2] && !dec_reg[1] && !dec_reg[15] && !dec_reg[14] && !dec_reg[13] && dec_reg[0];
assign M = !dec_reg[12] && !dec_reg[11] && !dec_reg[10] && !dec_reg[9] && !dec_reg[8] && !dec_reg[7] && dec_reg[6] && dec_reg[5] && dec_reg[4] && !dec_reg[3] && dec_reg[2] && dec_reg[1] && !dec_reg[15] && !dec_reg[14] && !dec_reg[13] && dec_reg[0];
assign N = !dec_reg[12] && !dec_reg[11] && !dec_reg[10] && !dec_reg[9] && !dec_reg[8] && !dec_reg[7] && !dec_reg[6] && !dec_reg[5] && dec_reg[4] && dec_reg[3] && dec_reg[2] && !dec_reg[1] && !dec_reg[15] && !dec_reg[14] && !dec_reg[13] && dec_reg[0];
assign O = !dec_reg[12] && !dec_reg[11] && dec_reg[10] && dec_reg[9] && dec_reg[8] && !dec_reg[7] && dec_reg[6] && dec_reg[5] && dec_reg[4] && !dec_reg[3] && dec_reg[2] && dec_reg[1] && !dec_reg[15] && !dec_reg[14] && !dec_reg[13] && dec_reg[0];
assign P = !dec_reg[12] && !dec_reg[11] && dec_reg[10] && !dec_reg[9] && dec_reg[8] && dec_reg[7] && dec_reg[6] && !dec_reg[5] && dec_reg[4] && dec_reg[3] && dec_reg[2] && !dec_reg[1] && !dec_reg[15] && !dec_reg[14] && !dec_reg[13] && dec_reg[0];
assign Q = dec_reg[12] && dec_reg[11] && dec_reg[10] && !dec_reg[9] && dec_reg[8] && dec_reg[7] && dec_reg[6] && !dec_reg[5] && dec_reg[4] && !dec_reg[3] && dec_reg[2] && dec_reg[1] && !dec_reg[15] && !dec_reg[14] && !dec_reg[13] && dec_reg[0];
assign R = !dec_reg[12] && !dec_reg[11] && !dec_reg[10] && !dec_reg[9] && !dec_reg[8] && !dec_reg[7] && dec_reg[6] && !dec_reg[5] && dec_reg[4] && dec_reg[3] && dec_reg[2] && !dec_reg[1] && !dec_reg[15] && !dec_reg[14] && !dec_reg[13] && dec_reg[0];
assign S = !dec_reg[12] && !dec_reg[11] && !dec_reg[10] && !dec_reg[9] && !dec_reg[8] && !dec_reg[7] && !dec_reg[6] && !dec_reg[5] && dec_reg[4] && !dec_reg[3] && dec_reg[2] && !dec_reg[1] && !dec_reg[15] && !dec_reg[14] && !dec_reg[13] && dec_reg[0];
assign T = !dec_reg[12] && !dec_reg[11] && !dec_reg[10] && !dec_reg[9] && !dec_reg[8] && !dec_reg[7] && !dec_reg[6] && !dec_reg[5] && !dec_reg[4] && !dec_reg[3] && dec_reg[2] && dec_reg[1] && !dec_reg[15] && !dec_reg[14] && !dec_reg[13] && dec_reg[0];
assign U = !dec_reg[12] && !dec_reg[11] && !dec_reg[10] && !dec_reg[9] && !dec_reg[8] && !dec_reg[7] && dec_reg[6] && !dec_reg[5] && dec_reg[4] && !dec_reg[3] && dec_reg[2] && dec_reg[1] && !dec_reg[15] && !dec_reg[14] && !dec_reg[13] && dec_reg[0];
assign V = !dec_reg[12] && !dec_reg[11] && !dec_reg[10] && !dec_reg[9] && dec_reg[8] && !dec_reg[7] && dec_reg[6] && !dec_reg[5] && dec_reg[4] && !dec_reg[3] && dec_reg[2] && dec_reg[1] && !dec_reg[15] && !dec_reg[14] && !dec_reg[13] && dec_reg[0];
assign W = !dec_reg[12] && !dec_reg[11] && !dec_reg[10] && !dec_reg[9] && dec_reg[8] && !dec_reg[7] && dec_reg[6] && dec_reg[5] && dec_reg[4] && !dec_reg[3] && dec_reg[2] && dec_reg[1] && !dec_reg[15] && !dec_reg[14] && !dec_reg[13] && dec_reg[0];
assign X = !dec_reg[12] && !dec_reg[11] && dec_reg[10] && dec_reg[9] && dec_reg[8] && !dec_reg[7] && dec_reg[6] && !dec_reg[5] && dec_reg[4] && !dec_reg[3] && dec_reg[2] && dec_reg[1] && !dec_reg[15] && !dec_reg[14] && !dec_reg[13] && dec_reg[0];
assign Y = dec_reg[12] && dec_reg[11] && dec_reg[10] && !dec_reg[9] && dec_reg[8] && !dec_reg[7] && dec_reg[6] && dec_reg[5] && dec_reg[4] && !dec_reg[3] && dec_reg[2] && dec_reg[1] && !dec_reg[15] && !dec_reg[14] && !dec_reg[13] && dec_reg[0];
assign Z = !dec_reg[12] && !dec_reg[11] && dec_reg[10] && dec_reg[9] && dec_reg[8] && !dec_reg[7] && dec_reg[6] && dec_reg[5] && dec_reg[4] && !dec_reg[3] && dec_reg[2] && !dec_reg[1] && !dec_reg[15] && !dec_reg[14] && !dec_reg[13] && dec_reg[0];
assign  valid =finish;
 /*A=1000001
	B=1000010
	C=1000011
	D=1000100
	E=1000101
	F=1000110
	G=1000111
	H=1001000
	I=1001001
	J=1001010
	K=1001011
	L=1001100
	M=1001101
	N=1001110
	O=1001111
	P=1010000
	Q=1010001
	R=1010010
	S=1010011
	T=1010100
	U=1010101
	V=1010110
	W=1010111
	X=1011000
	T=1011001
	Z=1011010*/
	always@ (posedge clk)
		begin
			if(enable) 
				begin
					if(!valid && !in[79] && !in[78] && !in[77])
						begin
							out_text = out_text  << 7 ;
							out_text[6] = 1 ;
							out_text[5] = 0 ;
							out_text[4] = P || Q || R || S || T || U || V  ||W ||X || Y || Z ;
							out_text[3] = H || I || J || K || L || M || N || O || X || Y || Z ;
							out_text[2] = D || E || F || G ||L || M || N || O || T || U || V || W ;
							out_text[1] = B || C || F || G ||J || K || N || O  || R || S || V || W || Z ;
							out_text[0] = A || C || E ||G || I ||K || M || O || Q || S || U ||W || Y ;
							
							dec_reg =0;
							in = in << 3;
							if(in == 0) //all clear 
								finish = 1;
						end
					else if (!valid ) // not three zero at [79] [78] [77]
						begin
							dec_reg = {dec_reg[14:0],in[79]};
							in = {in[78:0],1'b0};
							finish=0;
						end
				end
			 else 
				begin
					in = in_bits;
					finish=0;
				end
		end
endmodule
