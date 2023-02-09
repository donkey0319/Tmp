module lookahead_adder (
	input  [15:0] A, B,
	input         cin,
	output [15:0] S,
	output        cout
);
    /* TODO
     *
     * Insert code here to implement a CLA adder.
     * Your code should be completly combinational (don't use always_ff or always_latch).
     * Feel free to create sub-modules or other files. */
	  
	  logic cout1, cout2, cout3;
	 
	 four_bit_CLA CLA1(.A(A[3:0]), .B(B[3:0]), .cin(cin), .S(S[3:0]), .cout(cout1));
	 four_bit_CLA CLA2(.A(A[7:4]), .B(B[7:4]), .cin(cout1), .S(S[7:4]), .cout(cout2));
	 four_bit_CLA CLA3(.A(A[11:8]), .B(B[11:8]), .cin(cout2), .S(S[11:8]), .cout(cout3));
	 four_bit_CLA CLA4(.A(A[15:12]), .B(B[15:12]), .cin(cout3), .S(S[15:12]), .cout(cout));
	  

endmodule

// 4-bit CLA
module four_bit_CLA
(
input logic [3:0] A, B,
input logic cin,
output logic [3:0] S,
output logic cout
);

	logic [3:0] P, G, C;
	 
	 // Assigning P (= A^B)
	  assign P[0] = A[0]^B[0];
	  assign P[1] = A[1]^B[1];
	  assign P[2] = A[2]^B[2];
	  assign P[3] = A[3]^B[3];
	  
	 // Assigning G (= A&B)
	  assign G[0] = A[0]&B[0];
	  assign G[1] = A[1]&B[1];
	  assign G[2] = A[2]&B[2];
	  assign G[3] = A[3]&B[3];
	  
	 // Assigning C (Ci = Gi + Pi * ci-1)
	 assign C[0] = cin;
	 assign C[1] = cin * P[0] + G[0];
	 assign C[2] = cin * P[0] * P[1] + G[0] * P[1] + G[1];
	 assign C[3] = cin * P[0] * P[1] * P[2] + G[0] * P[1] * P[2] + G[1] * P[2] + G[2];
	 
	 // Assigning S (A^B^C)
	 assign S[0] = A[0]^B[0]^C[0];
	 assign S[1] = A[1]^B[1]^C[1];
	 assign S[2] = A[2]^B[2]^C[2];
	 assign S[3] = A[3]^B[3]^C[3];
	 
	 // Assigning Cout 
	 assign cout = cin * P[0] * P[1] * P[2] * P[3] + G[0] * P[1] * P[2] * P[3]+ G[1] * P[2] * P[3] + G[2] * P[3] + G[3];
	 
endmodule
