# Project 6: Hack Assembler - Translating Assembly to Machine Code

## Overview

In Project 6 of the Nand to Tetris course, you will build an **assembler**: a program that translates Hack assembly language into binary machine code that the Hack computer can execute. This project bridges the gap between human-readable code and the hardware-level instructions that drive the computer you built in previous projects.

---

## What is an Assembler?

An **assembler** is a tool that converts symbolic assembly instructions (like `@100`, `D=M`, `0;JMP`) into 16-bit binary instructions understood by the Hack CPU. This translation is essential for running any program on the Hack computer.

---

## Hack Assembly Language Recap

- **A-instruction**: `@value`  
  Loads a value into the A register.  
  Example: `@21` → `0000000000010101`

- **C-instruction**: `dest=comp;jump`  
  Performs computation and/or controls program flow.  
  Example: `D=M+1;JGT` → `1111110111010001`

- **Labels**: `(LOOP)`  
  Symbolic markers for jump destinations.

- **Variables**:  
  Symbols like `@i` or `@sum` are automatically assigned RAM addresses starting at 16.

---

## Assembler Workflow

The assembler operates in **two passes**:

1. **First Pass**:  
   - Scans the assembly file.
   - Records label definitions and their ROM addresses in a symbol table.

2. **Second Pass**:  
   - Translates each instruction to binary.
   - Resolves symbols (labels and variables) using the symbol table.
   - Allocates new RAM addresses for variables as needed.

---

## Key Features

- **Symbol Table**:  
  Maps symbols (labels, variables, predefined names like `R0`, `SCREEN`) to addresses.

- **Predefined Symbols**:  
  - `R0`-`R15` → RAM[0..15]
  - `SP`, `LCL`, `ARG`, `THIS`, `THAT`
  - `SCREEN` (16384), `KBD` (24576)

- **Instruction Translation**:  
  - A-instructions: Convert decimal or symbol to 16-bit binary.
  - C-instructions: Parse `dest`, `comp`, `jump` and map to binary using lookup tables.

- **Output**:  
  - Produces a `.hack` file with one 16-bit binary instruction per line.

---

## Example

**Input (`sum.asm`):**
```hack
@i
M=1
@sum
M=0
(LOOP)
@i
D=M
@100
D=D-A
@END
D;JGT
@i
D=M
@sum
M=M+D
@i
M=M+1
@LOOP
0;JMP
(END)
@END
0;JMP
```

**Output (`sum.hack`):**
```
0000000000010000
1110111111001000
0000000000010001
1110101010001000
0000000000010000
1111110000010000
0000000001100100
1111010011010000
0000000000011010
1110001100000001
...
```

---

## Usage

1. **Write your Hack assembly program** (e.g., `prog.asm`).
2. **Run the assembler**:
   ```
   ./assembler prog.asm
   ```
3. **Load the output `.hack` file** into the Hack computer simulator.

---

## Implementation Notes

- The assembler is typically implemented in C, Java, or Python.
- Uses hash tables or dictionaries for symbol management.
- Handles whitespace, comments, and error reporting.
- Follows the Hack machine language specification exactly.

---

## Project Goals

- Understand the translation from symbolic code to binary machine code.
- Implement a working assembler for the Hack platform.
- Deepen your understanding of the relationship between software and hardware.

---

## Resources

- [Hack Machine Language Specification](https://www.nand2tetris.org/project06)
- [Assembler API Reference](https://www.nand2tetris.org/software)
- [CPU Emulator](https://www.nand2tetris.org/software)
- "The Elements of Computing Systems" (Nisan & Schocken), Chapter 6

---
