module select_adder (
	input  [15:0] A, B,
	input         cin,
	output [15:0] S,
	output        cout
);

	  // FIRST Unit:
	  // 	set some logics here
	  logic C4, C8, C8_1, C8_2, C12, C12_1, C12_2, cout_1, cout_2;
	  
	  four_bit_full_adder FBFA_1(.A(A[3:0]), .B(B[3:0]), .cin(cin), .S(S[3:0]), .cout(C4));	  
	  
	  // SECOND Unit:
	  logic [3:0] A_In_1, B_In_1;
	  
	  four_bit_full_adder FBFA_20(.A(A[7:4]), .B(B[7:4]), .cin(0), .S(A_In_1), .cout(C8_1));
	  four_bit_full_adder FBFA_21(.A(A[7:4]), .B(B[7:4]), .cin(1), .S(B_In_1), .cout(C8_2));
	  
	  mux2_1 muxA(.S(C4), .A(A_In_1), .B(B_In_1), .S_out(S[7:4]));
	  
	  assign C8 = C8_1 | (C8_2 & C4);
	  
	  // THIRD Unit:
	  logic [3:0] A_In_2, B_In_2;
	  
	  four_bit_full_adder FBFA_30(.A(A[11:8]), .B(B[11:8]), .cin(0), .S(A_In_2), .cout(C12_1));
	  four_bit_full_adder FBFA_31(.A(A[11:8]), .B(B[11:8]), .cin(1), .S(B_In_2), .cout(C12_2));
	  
	  mux2_1 muxB(.S(C8), .A(A_In_2), .B(B_In_2), .S_out(S[11:8]));
	  
	  assign C12 = C12_1 | (C12_2 & C8);
	  
	  // FOURTH Unit:
	  logic [3:0] A_In_3, B_In_3;
	  
	  four_bit_full_adder FBFA_40(.A(A[15:12]), .B(B[15:12]), .cin(0), .S(A_In_3), .cout(cout_1));
	  four_bit_full_adder FBFA_41(.A(A[15:12]), .B(B[15:12]), .cin(1), .S(B_In_3), .cout(cout_2));
	  
	  mux2_1 muxC(.S(C12), .A(A_In_3), .B(B_In_3), .S_out(S[15:12]));
	  
	  assign cout = cout_1 | (cout_2 & C12);	
	  

endmodule


// MODULE four_bit_full_adder
module four_bit_full_adder(
	input logic [3:0] A, B,
	input logic cin,
	output logic [3:0] S,
	output logic cout
);

	logic [2:0] C;

	full_bit_adder FBA1(.A(A[0]), .B(B[0]), .cin(cin), .S(S[0]), .cout(C[0]));
	full_bit_adder FBA2(.A(A[1]), .B(B[1]), .cin(C[0]), .S(S[1]), .cout(C[1]));
	full_bit_adder FBA3(.A(A[2]), .B(B[2]), .cin(C[1]), .S(S[2]), .cout(C[2]));
	full_bit_adder FBA4(.A(A[3]), .B(B[3]), .cin(C[2]), .S(S[3]), .cout(cout));

endmodule 

// MODULE 2 to 1 MUX
module mux2_1(
	input S,
	input	logic [3:0] A_In, B_In,
	output logic [3:0] S_out
);
						
		always_comb
		begin
			unique case(S)
				1'b0: S_out = A_In;
				1'b1: S_out = B_In;
			endcase
		end
		
endmodule