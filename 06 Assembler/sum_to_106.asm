// Sums numbers from 1 to 106 and stores result in RAM[0]

@0
M=0        // sum = 0
@1
D=A
@i
M=D        // i = 1

(LOOP)
@i
D=M
@107
D=D-A
@END
D;JEQ      // if i == 107 goto END

@i
D=M
@0
M=M+D      // sum += i

@i
M=M+1      // i++

@LOOP
0;JMP

(END)
@END
0;JMP
