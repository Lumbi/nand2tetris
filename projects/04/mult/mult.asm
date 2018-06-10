// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Mult.asm

// Multiplies R0 and R1 and stores the result in R2.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)

// Begin

// Clear R2
@R2
M=0

// Check if R0 is zero

@R0
D=M
@ZERO
D;JEQ

// Check if R1 is zero

@R1
D=M
@ZERO
D;JEQ

// Add R0, R1 times

@R1
D=M
@FOR
M=D

(LOOP)

@R0
D=M
@R2
M=D+M

@FOR
M=M-1
D=M
@END
D;JLE

@LOOP
0;JMP

// Return zero

(ZERO)
@0
M=A
@END
0;JMP

// End

(END)
@FOR
M=0
@END
0;JMP
