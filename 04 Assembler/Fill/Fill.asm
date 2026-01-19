// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/4/Fill.asm

// Runs an infinite loop that listens to the keyboard input. 
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel. When no key is pressed, 
// the screen should be cleared.

(LOOP)
    @KBD
    D=M
    @BLACK
    D;JNE      // Jump to BLACK if key is pressed
    
    // Clear screen (white)
    @color
    M=0        // color = 0 (white)
    @FILL
    0;JMP
    
(BLACK)
    @color
    M=-1       // color = -1 (black)
    
(FILL)
    @8192      // Screen size in 16-bit words
    D=A
    @count
    M=D        // count = 8192
    
    @SCREEN
    D=A
    @addr
    M=D        // addr = SCREEN base address
    
(FILLLOOP)
    @count
    D=M
    @LOOP
    D;JEQ      // Return to LOOP when done
    
    @color
    D=M
    @addr
    A=M
    M=D        // RAM[addr] = color
    
    @addr
    M=M+1      // addr++
    @count
    M=M-1      // count--
    @FILLLOOP
    0;JMP