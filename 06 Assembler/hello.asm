// Prints "HELLO WORLD" to the screen (RAM[16384..])
// Each character is written to a consecutive memory location

@16384      // SCREEN base address
D=A
@addr
M=D         // addr = 16384

// H
@72
D=A
@addr
A=M
M=D
@addr
M=M+1

// E
@69
D=A
@addr
A=M
M=D
@addr
M=M+1

// L
@76
D=A
@addr
A=M
M=D
@addr
M=M+1

// L
@76
D=A
@addr
A=M
M=D
@addr
M=M+1

// O
@79
D=A
@addr
A=M
M=D
@addr
M=M+1

// (space)
@32
D=A
@addr
A=M
M=D
@addr
M=M+1

// W
@87
D=A
@addr
A=M
M=D
@addr
M=M+1

// O
@79
D=A
@addr
A=M
M=D
@addr
M=M+1

// R
@82
D=A
@addr
A=M
M=D
@addr
M=M+1

// L
@76
D=A
@addr
A=M
M=D
@addr
M=M+1

// D
@68
D=A
@addr
A=M
M=D
@addr
M=M+1

// Infinite loop
(END)
@END
0;JMP
