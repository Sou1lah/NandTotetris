// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/4/Mult.asm

// Multiplies R0 and R1 and stores the result in R2.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)
// The algorithm is based on repetitive addition.
@R2
M=0           // R2 = 0
@R0
D=M           // D = R0
@END
D;JLE         // if R0 <= 0, jump to END
@R1
D=M           // D = R1
@END
D;JLE         // if R1 <= 0, jump to END
@R0
D=M           // D = R0
@counter
M=D           // counter = R0
(LOOP)
@R1
D=M           // D = R1
@R2
M=D+M         // R2 = R2 + R1
@counter
MD=M-1        // counter--, store result in D
@LOOP
D;JGT         // if counter > 0, jump to LOOP
(END)
@END
0;JMP         // infinite loop