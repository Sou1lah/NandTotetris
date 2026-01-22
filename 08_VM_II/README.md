# Project 8: Virtual Machine II – Program Control & Functions

## Overview

Project 8 is the second part of the Virtual Machine (VM) Translator in the Nand to Tetris course. Building on Project 7, which handled stack arithmetic and memory access, this project extends your VM translator to support **program control** (labels, goto, if-goto) and **function calling** (function, call, return) commands. You will also handle multi-file VM programs and bootstrap code.

---

## What’s New in Project 8?

- **Program Control Commands**:  
  - `label`, `goto`, `if-goto`
- **Function Calling Commands**:  
  - `function`, `call`, `return`
- **Multi-file Support**:  
  - Translate all `.vm` files in a directory, producing a single `.asm` output.
- **Bootstrap Code**:  
  - Initialize the stack and call `Sys.init` at program start.

---

## VM Language Recap

- **Arithmetic Commands**: `add`, `sub`, `neg`, `eq`, `gt`, `lt`, `and`, `or`, `not`
- **Memory Access**: `push segment index`, `pop segment index`
- **Program Control**: `label`, `goto`, `if-goto`
- **Function Calling**: `function`, `call`, `return`

---

## Project Workflow

The VM translator now operates in multiple passes:

1. **Parsing**:
   - Reads VM commands from one or more `.vm` files.
   - Removes whitespace and comments.
   - Determines the command type and extracts arguments.

2. **Code Generation**:
   - Translates each VM command into Hack assembly instructions.
   - Handles arithmetic/logical operations, memory access, program control, and function calling.
   - Generates unique labels for branching and function return addresses.
   - Handles static variables uniquely per file.

3. **Bootstrap**:
   - Writes assembly code to initialize the stack pointer and call `Sys.init` before translating any VM code.

4. **Output**:
   - Produces a single `.asm` file with Hack assembly code for all input `.vm` files.

---

## Key Features

- **Parser**: Reads and cleans VM commands, identifies command types, and extracts arguments.
- **Code Generator**: Converts all VM commands (including program control and functions) to Hack assembly.
- **Label Generation**: Ensures unique labels for branching and function returns.
- **Multi-file Handling**: Processes all `.vm` files in a directory, managing static variables per file.
- **Bootstrap Code**: Initializes the stack and starts the program correctly.

---

## Example

**Input (`Main.vm`):**
```
function SimpleFunction.test 2
push constant 10
push constant 20
add
pop local 0
push argument 0
return
```

**Output (`Main.asm`):**
```asm
// Bootstrap code (if present)
@256
D=A
@SP
M=D
// function SimpleFunction.test 2
(SimpleFunction.test)
@0
D=A
@LCL
A=M+D
M=0
@1
D=A
@LCL
A=M+D
M=0
// push constant 10
@10
D=A
@SP
A=M
M=D
@SP
M=M+1
// ... etc ...
```

---

## Usage

1. **Write your VM program** (can be multiple `.vm` files in a directory).
2. **Compile the VM translator**:
   ```
   gcc -Wall -Werror vm.c -o vm
   ```
3. **Run the translator**:
   ```
   ./vm <input_file>.vm
   ```
   or for a directory:
   ```
   ./vm <directory>
   ```
4. **Load the output `.asm` file** into the Hack platform or CPU emulator.

---

## Implementation Notes

- The VM translator is implemented in C.
- The parser section handles reading, cleaning, and parsing VM commands.
- The code generator section translates all VM commands, including program control and function calls.
- Unique labels are generated for branching and function return addresses.
- Bootstrap code is required for multi-file programs.

---

## Project Goals

- Understand program control flow and function calling in a stack-based VM.
- Implement a complete VM translator for all VM commands.
- Deepen your understanding of translating high-level constructs to low-level machine instructions.

---

## Resources

- [VM Specification](https://www.nand2tetris.org/project08)
- [Hack Platform](https://www.nand2tetris.org/software)
- [CPU Emulator](https://www.nand2tetris.org/software)
- "The Elements of Computing Systems" (Nisan & Schocken), Chapter 8


## Detailed Explanation of `vm.c` Functions

Below is a function-by-function explanation of the main C file for this project, describing what each function does and how it serves the Nand2Tetris Virtual Machine Translator:

### Enum: Command Types
```c
enum {
   C_ARITHMETIC, C_PUSH, C_POP, C_LABEL, C_GOTO, C_IF, C_FUNCTION, C_RETURN, C_CALL, C_UNKNOWN
};
```
Defines constants for each VM command type, making it easier to identify and handle different commands in the code generator.

### int hasMoreCommands(FILE *vmfile)
Checks if there are more commands to read from the VM file. Returns 1 if more commands exist, 0 otherwise. Used to control the main parsing loop.

### int advance(FILE *vmfile, char *command)
Reads the next valid VM command from the file, skipping comments and whitespace. Stores the cleaned command in `command`. Returns 1 if a command was read, 0 if end of file. This is the main input function for the parser.

### int commandType(char *command)
Determines the type of the current VM command (push, pop, arithmetic, etc.) by inspecting the command string. Returns the corresponding enum value. This is essential for dispatching the correct code generation routine.

### void arg1(char *command, char *arg)
Extracts the first argument of the command (e.g., segment name or arithmetic operation). For arithmetic commands, returns the command itself. Used to get the segment or operation for code generation.

### int arg2(char *command)
Extracts the second argument of the command (usually an index for push/pop). Returns the integer value or -1 if not applicable. Used for memory access commands.

### void writeArithmetic(const char *cmd, FILE *out)
Translates arithmetic and logical VM commands (add, sub, neg, eq, gt, lt, and, or, not) into Hack assembly and writes them to the output file. Handles label generation for comparison commands. This is a core part of the code generator.

### void writePush(const char *segment, int index, FILE *out)
Translates a `push` command for the given segment and index into Hack assembly. Handles all memory segments (constant, local, argument, this, that, temp, pointer, static). Writes the result to the output file.

### void writePop(const char *segment, int index, FILE *out)
Translates a `pop` command for the given segment and index into Hack assembly. Handles all memory segments except constant. Writes the result to the output file.

### int labelCounter, static char currentFileName[64]
Global variables used for generating unique labels and tracking the current file name for static variables.

### char* generateLabel(const char *base)
Generates a unique label string based on a base name and a counter. Used for branching and comparison commands to avoid label collisions.

### void setFileName(const char *filename)
Extracts and stores the base name of the current VM file (without extension) for use in static variable naming. Ensures static variables are unique per file.

### int main(int argc, char **argv)
The entry point of the program. Currently a placeholder (`TODO`). In the full implementation, it will handle file input/output, call the parser and code generator functions, and produce the final `.asm` file.

---

**How these functions serve the course:**

These functions together implement the core of a VM-to-Hack translator, a key step in the Nand2Tetris course. They allow you to parse high-level VM commands, identify their types and arguments, and generate the corresponding low-level Hack assembly code. This process is essential for understanding how high-level programming constructs are translated into machine instructions, deepening your understanding of computer architecture and compilation.