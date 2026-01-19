

# **Hack Assembler Project Plan (C, Optimized)**

### **Goal**

Build a **Hack assembler** that reads a `.asm` file and outputs a `.hack` file containing **16-bit binary machine code**, using **hash tables for symbol management** and **lookup tables** for instruction translation.

---

## **Step 0: Setup**

* Install a C compiler (GCC/Clang).
* Create project structure:

```
/hack-assembler
  main.c
  parser.c / parser.h
  symbol_table.c / symbol_table.h
  code.c / code.h
  utils.c / utils.h
```

* Create a simple `.asm` file for testing:

```asm
@2
D=A
@3
D=D+A
@0
M=D
```

---

## **Step 1: File Reading and Cleaning (Mini Project 1)**

* **Goal:** Read `.asm` file line by line, remove whitespace and comments.
* Implement:

  * `readLine(FILE *file, char *buffer)`
  * `stripCommentsAndWhitespace(char *line)`
* **Checkpoint:** Print cleaned lines to console.
* **Complexity:** O(L) for L lines.

---

## **Step 2: Instruction Detection**

* **Goal:** Detect whether a line is:

  * **A-instruction** (`@value`)
  * **C-instruction** (`dest=comp;jump`)
  * **Label** (`(LOOP)`)
* Implement:

  * `int getInstructionType(char *line)` → returns A, C, or LABEL
* **Checkpoint:** Print type for each line.

---

## **Step 3: Build Symbol Table (First Pass)**

* **Goal:** Record all labels `(LABEL)` with their line numbers.
* Implement **hash table**:

  * `insertSymbol(char *name, int address)`
  * `getSymbolAddress(char *name)`
  * Hash function for strings
* Preload predefined symbols:

  ```
  SP=0, LCL=1, ARG=2, THIS=3, THAT=4, R0-R15, SCREEN=16384, KBD=24576
  ```
* **Checkpoint:** Print hash table contents after first pass.

---

## **Step 4: Translate A-instructions**

* **Goal:** Convert `@value` into 16-bit binary:

  * Numeric: `@21` → `0000000000010101`
  * Symbol: look up hash table, assign address if new variable (starting from 16)
* Implement:

  * `char* translateA(char *symbol_or_number)`
* **Checkpoint:** Test `@2`, `@i`, `@LOOP`.

---

## **Step 5: Translate C-instructions**

* **Goal:** Convert `dest=comp;jump` into binary:

  * Use **lookup tables** for `comp`, `dest`, `jump`.
* Implement:

  * `char* translateC(char *line)`
  * Split line into dest/comp/jump
  * Map each using table
* **Checkpoint:** Test with examples like `D=A`, `D=D+A`, `0;JMP`.

---

## **Step 6: Second Pass and File Output**

* **Goal:** Loop through cleaned instructions and:

  1. Translate A or C instruction to 16-bit binary
  2. Write to `.hack` file
* Implement:

  * `writeHackFile(char *output_file, char **lines, int n)`
* **Checkpoint:** `.hack` file matches expected output.

---

## **Step 7: Testing**

* Create multiple `.asm` test programs:

  * Simple arithmetic
  * Loops and labels
  * Variables
* Compare `.hack` output with **official Hack simulator**.

---

## **Step 8: Optimization and Cleanup**

* Ensure hash table uses chaining efficiently
* Use `strdup` carefully to avoid memory leaks
* Modularize code into `parser.c`, `code.c`, `symbol_table.c`
* Add comments for readability

---

## **Optional Bonus Features**

* **Command-line arguments** for input/output filenames
* **Error handling**: undefined symbols, invalid instructions
* **Memory leak check** using `valgrind`
