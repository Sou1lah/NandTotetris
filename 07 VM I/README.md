# Project 7: Virtual Machine I – Stack Arithmetic

## Overview

In Project 7 of the Nand to Tetris course, you will build the first part of a **Virtual Machine (VM) translator**. This project introduces a stack-based, platform-independent VM language and requires you to implement a translator that converts VM commands into Hack assembly code. This is a crucial step in bridging high-level programming and hardware execution.

---

## What is a Virtual Machine?

A **Virtual Machine** is an abstract computer that provides a uniform platform for running programs, regardless of the underlying hardware. The VM language is stack-based and designed to be simple, making it easy to translate into the Hack assembly language.

---

## VM Language Recap

- **Arithmetic Commands**: `add`, `sub`, `neg`, `eq`, `gt`, `lt`, `and`, `or`, `not`
- **Memory Access Commands**: `push segment index`, `pop segment index`
  - Segments: `constant`, `local`, `argument`, `this`, `that`, `temp`, `pointer`, `static`

---

## Project Workflow

The VM translator operates in a single pass for Project 7:

1. **Parsing**:
   - Reads VM commands from one or more `.vm` files.
   - Removes whitespace and comments.
   - Determines the command type and extracts arguments.

2. **Code Generation**:
   - Translates each VM command into Hack assembly instructions.
   - Handles arithmetic/logical operations and memory access (push/pop) for all segments.
   - Generates unique labels for comparison operations (`eq`, `gt`, `lt`).

3. **Output**:
   - Produces a `.asm` file with Hack assembly code that can be run on the Hack platform.

---

## Key Features

- **Parser**: Reads and cleans VM commands, identifies command types, and extracts arguments.
- **Code Generator**: Converts VM commands to Hack assembly, handling stack operations and memory segments.
- **Label Generation**: Ensures unique labels for comparison operations to avoid conflicts.

---

## Example

**Input (`test.vm`):**
```
push constant 7
push constant 8
add
pop local 0
push constant 3
sub
```

**Output (`test.asm`):**
```asm
@7
D=A
@SP
A=M
M=D
@SP
M=M+1
@8
D=A
@SP
A=M
M=D
@SP
M=M+1
@SP
AM=M-1
D=M
A=A-1
M=M+D
@SP
AM=M-1
D=M
@LCL
A=M
M=D
@3
D=A
@SP
A=M
M=D
@SP
M=M+1
@SP
AM=M-1
D=M
A=A-1
M=M-D
```

---

## Usage

1. **Write your VM program** (e.g., `test.vm`).
2. **Compile the VM translator**:
   ```
   gcc -Wall -Werror VM.c -o vm
   ```
3. **Run the translator**:
   ```
   ./vm
   ```
   - Enter the input VM file name (e.g., `test.vm`).
   - Enter the output ASM file name (e.g., `test.asm`).
4. **Load the output `.asm` file** into the Hack platform or CPU emulator.

---

## Implementation Notes

- The VM translator is implemented in C.
- The parser section handles reading, cleaning, and parsing VM commands.
- The code generator section translates commands to Hack assembly, handling stack and memory segments as specified in the Nand2Tetris course.
- Unique labels are generated for comparison commands to ensure correct branching.

---

## Project Goals

- Understand the design and implementation of a stack-based virtual machine.
- Implement a working VM translator for arithmetic and memory access commands.
- Deepen your understanding of the translation from high-level code to low-level machine instructions.

---

## Resources

- [VM Specification](https://www.nand2tetris.org/project07)
- [Hack Platform](https://www.nand2tetris.org/software)
- [CPU Emulator](https://www.nand2tetris.org/software)
- "The Elements of Computing Systems" (Nisan & Schocken), Chapter 7

---
