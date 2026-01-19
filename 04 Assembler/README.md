# Hack Assembly I: The Basics - Complete Guide

## Course Overview

This guide covers **Hack Assembly**, the low-level programming language for the Hack computer architecture. Assembly is one of the earliest forms of programming, and understanding it is fundamental to computer architecture. While we won't build production systems in assembly, learning Hack assembly prepares you to understand any CPU architecture and optimize performance-critical code.

---

## Historical Context: Why Assembly?

### The Early Days of Computing (1949)
In 1949, EDSAC was one of the first stored-program computers to go into regular use. From the very beginning, programmers **didn't want to write in machine code** (raw binary). Instead, they used **mnemonics** — one line of text per instruction.

This invention led to the first **assembly language**, which became ubiquitous by the 1950s. A tool called an **assembler** translates human-readable assembly into machine code that computers can execute.

### Why Learn Assembly Today?

1. **Universal Principles**: Different architectures (x86-64, ARM, MIPS) have different assembly languages, but the concepts are the same.
2. **Performance**: Optimized assembly code is often faster than compiled code in high-performance languages (C, C++, Rust).
3. **Understanding**: Assembly teaches you how computers *really* work at the hardware level.

### ⚠️ Important Warning
Assembly is **not portable, legible, or easily maintainable**. Only optimize with assembly when:
- You've identified a performance bottleneck using profiling tools
- You can justify the trade-off in readability vs. speed
- Remember: **Premature optimization is a bad idea**

---

## The Hack Computer Architecture

### Registers

The Hack CPU has **4 registers**, each holding a 16-bit word:

#### **A (Address Register)**
- Used to load values directly
- The only register we can initialize with literal numbers using `@value`
- Interprets values as memory addresses
- Affects the behavior of the M register

#### **D (Data Register)**
- General-purpose storage
- Unlike A, writing to D doesn't affect memory access
- Can be used for long-term or temporary data storage

#### **M (Memory Register)**
- A "virtual" register that represents RAM memory
- **When read**: Returns `RAM[A]` (dereferencing A like a pointer in C)
- **When written**: Updates `RAM[A]`
- Creates a bridge between registers and RAM

#### **PC (Program Counter)**
- Points to the next instruction to execute: `ROM[PC]`
- Writing to PC allows jumping to different parts of code
- Behaves differently from other registers (see control flow)

---

## Hack Assembly Syntax

### Loading Values

```
@[number]     // Load literal number into register A
@42           // Sets A to 42
@R0           // Loads 0 into A (R0 is a keyword for address 0)
@myVar        // Loads address of variable myVar into A
```

### Operations on Registers

All operations (except `@` statements) follow this pattern:

#### **Constants**
```
D = 0      // Assign 0
D = 1      // Assign 1
A = -1     // Assign -1
```

#### **Unary Operations**
```
D = A      // Identity (copy A to D)
A = -D     // Negation (negate D, store in A)
D = !D     // Bitwise NOT (flip all bits)
A = A + 1  // Increment
M = M - 1  // Decrement
```

#### **Binary Operations**
```
D = A + D  // Addition
M = M - D  // Subtraction
D = D & A  // Bitwise AND
A = D | M  // Bitwise OR
```

**⚠️ Important Constraints:**
- Binary operations must involve **exactly 2 different registers**, and **at least one must be D**
- **Invalid**: `D = A + M` (both non-D), `M = D + D` (same register twice)
- **Invalid**: `D = 17` (constants only in assignment), `A = D + M + A` (more than 2 operands)

#### **Multiple Assignment**
```
MD = D - M      // Store D - M in both M and D
AMD = D + A     // Store D + A in all three: A, M, D
D = A + 1       // Only D gets the result
```
**Note**: When multiple registers are assigned, they must appear in order: A, M, D

---

## Practical Examples

### Example 1: Simple Addition
Calculate `RAM[0] + RAM[1] + 17` and store in `RAM[2]`:

```hack
// D <- RAM[0]
@R0
D = M

// D <- D + RAM[1]
@R1
D = D + M

// D <- D + 17
@17
D = D + A

// RAM[2] <- D
@R2
M = D

// Infinite loop (end every program this way)
(LOOP)
@LOOP
0;JMP
```

**Breakdown:**
1. `@R0` → Load address 0 into A
2. `D = M` → Copy value at RAM[0] into D
3. `@R1` → Load address 1 into A
4. `D = D + M` → Add RAM[1] to D
5. `@17` → Load literal 17 into A
6. `D = D + A` → Add 17 to D
7. `@R2` → Load address 2 into A
8. `M = D` → Store result in RAM[2]

### Example 2: Using Variables
Same logic with named variables (more readable):

```hack
// D <- RAM[R0]
@R0
D = M

// D <- D + RAM[R1]
@R1
D = D + M

// D <- D + 17
@17
D = D + A

// RAM[R2] <- D
@R2
M = D

(END)
@END
0;JMP
```

---

## Helpful Features: Comments & Keywords

### Comments
The assembler ignores:
- Lines starting with `//`
- Empty lines and leading whitespace
- Mid-line comments: `D = A // Add A to D`

### Virtual Registers (R0-R15)
```hack
@R0   // Replaces @0
@R1   // Replaces @1
@R15  // Replaces @15
```

These correspond to RAM addresses 0-15, reserved for I/O and data storage.

### Other Keywords (coming later)
- `SP` → 0 (Stack Pointer)
- `LCL` → 1 (Local variables)
- `ARG` → 2 (Arguments)
- `THIS` → 3 (Object pointer)
- `THAT` → 4 (Another pointer)
- `SCREEN` → 16384 (Video memory)
- `KBD` → 24576 (Keyboard input)

---

## Variables in Hack Assembly

### How Variables Work

The assembler automatically handles alphabetical variables:

```hack
@myVar      // First use: assigns myVar to RAM[16]
D = M       // Subsequent uses reuse the same address
@myVar      // Also refers to RAM[16]
D = D + A
```

**Key Points:**
- First use of `@variableName` assigns it a unique RAM address (starting from 16)
- **Case-sensitive**: `foo`, `Foo`, and `FOO` are different variables
- Variables in order: `@foo` → 16, `@Foo` → 17, `@FOO` → 18
- **These are NOT like C variables** — no types, no automatic memory management!

### Use Variables When:
✅ Storing input/output data  
✅ Naming constants or addresses  
✅ Improving code readability  

### Don't Use Variables When:
❌ Managing large arrays (manually use addresses)  
❌ Storing runtime-sized data structures  
❌ Working with special memory regions (like SCREEN)  

---

## Project Goals: Building an Assembler

By the end of this phase, you'll:

1. **Understand Hack Assembly Syntax**
   - How to read and write assembly instructions
   - The constraints of the instruction set
   - When to use variables vs. addresses

2. **Write Functional Assembly Programs**
   - Perform arithmetic operations
   - Access and manipulate memory
   - Implement loops and conditionals (control flow)
   - Work with input/output through virtual registers

3. **Build an Assembler**
   - Parse assembly syntax
   - Convert mnemonics to binary machine code
   - Handle symbols, variables, and labels
   - Produce executable ROM files

4. **Debug Assembly Code**
   - Use the CPU simulator to trace execution
   - Understand register and memory state changes
   - Verify program behavior step-by-step

---

## Quick Reference: Operations Table

| Category | Operation | Example |
|----------|-----------|---------|
| **Load** | Load value into A | `@42` |
| **Constants** | Zero | `D = 0` |
| | One | `D = 1` |
| | Negative one | `A = -1` |
| **Unary** | Copy | `D = A` |
| | Negate | `A = -D` |
| | Bitwise NOT | `D = !D` |
| | Increment | `A = A + 1` |
| | Decrement | `M = M - 1` |
| **Binary** | Add | `D = A + D` |
| | Subtract | `M = M - D` |
| | AND | `D = D & A` |
| | OR | `A = D \| M` |
| **Multi-assign** | Multiple targets | `MD = D - M` |

---

## Getting Started: Next Steps

1. **Practice simple arithmetic** with the examples above
2. **Understand the CPU simulator** — trace through `add.asm` step-by-step
3. **Write small programs** that:
   - Sum two numbers and store the result
   - Multiply using repeated addition
   - Work with memory arrays
4. **Implement an assembler** that translates assembly to machine code
5. **Test on the CPU simulator** to verify correctness

---

## Key Concepts to Remember

| Concept | Remember |
|---------|----------|
| **A Register** | Use for loading values and addressing memory |
| **D Register** | General-purpose data storage; doesn't affect M |
| **M Register** | Memory access via address in A (pointer semantics) |
| **Binary Ops** | Must use exactly 2 registers, at least one is D |
| **Variables** | Automatically assigned RAM[16] and beyond; case-sensitive |
| **Comments** | `//` for single-line, use liberally! |
| **Infinite Loop** | Every program ends with a loop back to itself |

---

## Resources

- **Hack Assembler Tool**: Available in the course materials
- **CPU Simulator**: Test programs visually with step-by-step execution
- **Machine Code Reference**: Coming next (after understanding assembly syntax)

---

**Ready to write assembly? Start with simple programs and work your way up. Leverage comments and variables to keep your code readable. Good luck!**
