(START) // ROM = 0 = jump
@10      // A-instruction with number
D=A
@LOOP    // A-instruction with label (to be resolved)
0;JMP
(LOOP)   // Label
@R0      // A-instruction with predefined symbol
M=D
@SCREEN  // Another predefined symbol
D=M
