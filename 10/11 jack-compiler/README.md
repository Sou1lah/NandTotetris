# Jack Compiler Workflow (Start to Finish)

This document explains, step by step, how a Jack compiler should work from **start to finish**, mapping Projects 10 and 11 into a clear workflow for implementation in C.

---

## 1. Input Stage

**Files:** `.jack` source files

**Responsibilities:**

* Receive either a single Jack file or a directory of files
* Validate that files have `.jack` extension
* Open each file for reading

**Tools:** `main.c`

**Notes:**

* Project 10 assumes files are syntactically correct
* No error checking at this stage for invalid syntax

---

## 2. Tokenization (Lexical Analysis)

**Files:** `tokenizer.c`, `tokenizer.h`

**Responsibilities:**

* Remove comments (`//`, `/* */`) and extra whitespace
* Split text into **tokens**: keywords, symbols, identifiers, integer constants, string constants
* Provide methods for parser to access current token, advance, and query type

**Output:** Stream of tokens

**Core Functions:**

* `hasMoreTokens()`
* `advance()`
* `tokenType()`
* `keyword()`
* `symbol()`
* `identifier()`
* `intVal()`
* `stringVal()`

**Notes:**

* This is purely mechanical; no grammar understanding yet

---

## 3. Parsing (Syntax Analysis)

**Files:** `parser.c`, `parser.h`

**Responsibilities:**

* Consume tokens from tokenizer
* Validate syntax according to Jack grammar
* Build **parse tree** (initially in XML for Project 10)
* Functions correspond to grammar rules (recursive descent parser)

**Key Routines:**

* `compileClass()`
* `compileClassVarDec()`
* `compileSubroutine()`
* `compileStatements()`
* `compileExpression()`
* `compileTerm()`

**Output:**

* **Project 10:** XML representation of parsed program
* **Project 11:** VM commands generated instead of XML

**Notes:**

* Parser drives the compilation process
* Handles recursive grammar naturally

---

## 4. Symbol Table (Semantic Analysis)

**Files:** `symbol_table.c`, `symbol_table.h`

**Responsibilities:**

* Track all identifiers with metadata:

  * name
  * type (int, boolean, class name, etc.)
  * kind (static, field, arg, var)
  * index (running count per kind)
  * scope (class/subroutine)
* Support queries from parser for code generation
* Reset subroutine scope for each function/method

**Output:**

* Metadata available for parser and VMWriter

**Core Functions:**

* `startClass()`
* `startSubroutine()`
* `define()`
* `kindOf()`
* `typeOf()`
* `indexOf()`

---

## 5. VM Code Generation

**Files:** `vm_writer.c`, `vm_writer.h`

**Responsibilities:**

* Output **Hack VM commands** for each construct
* Translate Jack statements and expressions to stack-based VM code

**Examples:**

| Jack Construct      | VM Output                      |
| ------------------- | ------------------------------ |
| let x = 5;          | push constant 5 \ pop local 0  |
| if (...) { ... }    | label, if-goto, goto sequences |
| while (...) { ... } | loop labels + goto             |
| do subroutine()     | call + pop temp                |
| return expr;        | compile expr + return          |

**Core Functions:**

* `writePush()`
* `writePop()`
* `writeArithmetic()`
* `writeLabel()`
* `writeGoto()`
* `writeIf()`
* `writeCall()`
* `writeFunction()`
* `writeReturn()`

**Notes:**

* VMWriter abstracts away file writing and VM formatting
* Parser calls VMWriter whenever a code construct is encountered

---

## 6. Testing and Verification

**Steps:**

1. Compile Jack source using your compiler → produces `.vm` files
2. Load `.vm` files into **VM Emulator**
3. Run test programs (Seven, ConvertToBin, Square, Average, Pong, ComplexArrays)
4. Compare output with expected behavior
5. Debug compiler if errors occur (programs are correct)

**Notes:**

* Each test program builds on previous ones
* Start with simplest programs to verify foundational features

---

## 7. Output Stage

**Result:**

* A set of `.vm` files, one per `.jack` source file
* Fully executable on Hack VM emulator
* Ready for further compilation to Hack assembly (later projects)

**Summary Pipeline:**

```
.jack (source files)
   ↓ Tokenizer
   ↓ Parser / CompilationEngine
   ↓ SymbolTable (semantic info)
   ↓ VMWriter
   ↓ .vm files (Hack VM code)
   ↓ VM Emulator
```

## Structure Overview

```Jack Source (.jack)
     │
     ▼
Tokenizer (lexical analysis)
- Reads characters
- Groups into tokens (keywords, symbols, identifiers, integers, strings)
- Stores currentToken + currentType
     │
     ▼
Parser (syntax analysis)
- Reads tokens using getters
- Understands program structure: class, subroutine, statements, expressions
- Calls Symbol Table when it sees variables/functions
     │
     ▼
Symbol Table (semantic analysis)
- Stores variables: name, type, kind (static/field/arg/var), index
- Keeps track of scope (class/subroutine)
- Tells parser/VM writer where each variable lives
     │
     ▼
VM Writer (code generation)
- Generates stack-based Hack VM commands
- Examples: push/pop, arithmetic, function call, return
- Uses Symbol Table info to decide memory segments (local/this/static/argument)
     │
     ▼
VM Output (.vm)
- Human-readable stack code
- Example:
    push constant 5
    pop local 0
    return
     │
     ▼
Hack Assembler / VM Translator
- Converts VM commands → Hack assembly → binary (0s and 1s)
- Example:
    push constant 5 → @5, D=A, @SP, A=M, M=D, @SP, M=M+1
- Final output → Hack machine code (.hack)
- Can be loaded into the Hack CPU simulator
```