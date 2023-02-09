module ripple_adder
(
	input  [15:0] A, B,
	input         cin,
	output [15:0] S,
	output        cout
);

    /* TODO
     *
     * Insert code here to implement a ripple adder.
     * Your code should be completly combinational (don't use always_ff or always_latch).
     * Feel free to create sub-modules or other files. */
	  
	  logic c1, c2, c3, c4, c5, c6, c7, c8, c9, c10, c11, c12, c13, c14, c15;
	  
			full_bit_adder FBA0(.A(A[0]), .B(B[0]), .cin(cin), .S(S[0]), .cout(c1));
			full_bit_adder FBA1(.A(A[1]), .B(B[1]), .cin(c1), .S(S[1]), .cout(c2));
			full_bit_adder FBA2(.A(A[2]), .B(B[2]), .cin(c2), .S(S[2]), .cout(c3));
			full_bit_adder FBA3(.A(A[3]), .B(B[3]), .cin(c3), .S(S[3]), .cout(c4));
			full_bit_adder FBA4(.A(A[4]), .B(B[4]), .cin(c4), .S(S[4]), .cout(c5));
			full_bit_adder FBA5(.A(A[5]), .B(B[5]), .cin(c5), .S(S[5]), .cout(c6));
			full_bit_adder FBA6(.A(A[6]), .B(B[6]), .cin(c6), .S(S[6]), .cout(c7));
			full_bit_adder FBA7(.A(A[7]), .B(B[7]), .cin(c7), .S(S[7]), .cout(c8));
			full_bit_adder FBA8(.A(A[8]), .B(B[8]), .cin(c8), .S(S[8]), .cout(c9));
			full_bit_adder FBA9(.A(A[9]), .B(B[9]), .cin(c9), .S(S[9]), .cout(c10));
			full_bit_adder FBA10(.A(A[10]), .B(B[10]), .cin(c10), .S(S[10]), .cout(c11));
			full_bit_adder FBA11(.A(A[11]), .B(B[11]), .cin(c11), .S(S[11]), .cout(c12));
			full_bit_adder FBA12(.A(A[12]), .B(B[12]), .cin(c12), .S(S[12]), .cout(c13));
			full_bit_adder FBA13(.A(A[13]), .B(B[13]), .cin(c13), .S(S[13]), .cout(c14));
			full_bit_adder FBA14(.A(A[14]), .B(B[14]), .cin(c14), .S(S[14]), .cout(c15));
			full_bit_adder FBA15(.A(A[15]), .B(B[15]), .cin(c15), .S(S[15]), .cout(cout));

     
endmodule


module full_bit_adder
(	input logic A, B, cin,
	output logic S, cout);

	always_comb
	begin
		S = A ^ B ^ cin;
		cout = (A&B) | (B&cin) | (A&cin);
	end

endmodule
	