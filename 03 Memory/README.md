![Memory Hierarchy](https://www.tutorialspoint.com/digital-electronics/images/memory-hierarchy.jpg)

## DFF (Gate)

A flip-flop is a sequential digital electronic circuit having two stable  states that can be used to store one bit of binary data. Flip-flops are  the fundamental building blocks of all memory devices.

### Types of Flip-Flops

* S-R Flip-Flop
* J-K Flip-Flop
* D Flip-Flop
* T Flip-Flop

### S-R Flip-Flop

This is the simplest flip-flop circuit. It has a set input (S) and a  reset input (R). When in this circuit when S is set as active, the  output Q would be high and the Q' will be low. If R is set to active  then the output Q is low and the Q' is high. Once the outputs are  established, the results of the circuit are maintained until S or R get  changed, or the power is turned off.

![S-R Flip-Flop](https://www.tutorialspoint.com/digital-electronics/images/sr-flip-flop.jpg)

### J-K Flip-Flop

Because of the invalid state corresponding to S=R=1 in the SR  flip-flop, there is a need of another flip-flop. The JK flip-flop  operates with only positive or negative clock transitions. The operation  of the JK flip-flop is similar to the SR flip-flop. When the input J  and K are different then the output Q takes the value of J at the next  clock edge.

When J and K both are low then NO change occurs at the output. If  both J and K are high, then at the clock edge, the output will toggle  from one state to the other.

![J-K Flip-Flop](https://www.tutorialspoint.com/digital-electronics/images/jk-flip-flop.jpg)

### T Flip-Flop

A T flip-flop (Toggle Flip-flop) is a simplified version of JK  flip-flop. The T flop is obtained by connecting the J and K inputs  together. The flip-flop has one input terminal and clock input. These  flip-flops are said to be T flip-flops because of their ability to  toggle the input state. Toggle flip-flops are mostly used in counters.

![T Flip-Flop](https://www.tutorialspoint.com/digital-electronics/images/t-flip-flop.jpg)

### What is D Flip Flop?

The D flip-flop is a clocked flip-flop with a single digital input  'D'. Each time a D flip-flop is clocked, its output follows the state of  'D'. The D Flip Flop has only two inputs D and CP. The D inputs go  precisely to the S input and its complement is used to the R input.

Considering the pulse input is at 0, the outputs of gates 3 and 4 are  at the 1 level and the circuit cannot convert state regardless of the  value of D. The D input is sampled when CP = 1. If D is 1, the Q output  goes to 1, locating the circuit in the set state. If D is 0, output Q  goes to 0, and the circuit switches to a clear state.

![](https://www.tutorialspoint.com/digital-electronics/images/what-is-d-flip-flop.jpg)

## register

In digital electronic devices and systems, **binary registers**  are one of the crucial components that play a vital role in data storage  and manipulation. Binary registers are the fundamental building blocks  in memory unit of a digital system or device.

Here, we will explore basics of **binary registers** and **binary register data**. So, lets start with the basic introduction of binary registers.

### What are Binary Registers?

In digital systems, a **binary register** is considered the base  of a data storage unit. It is a group of flip-flops connected together  to store data and information in the form of **0s** and **1s**.  The storage capacity of a binary register depends upon the number of  flip-flop combined in the circuit. For example, a 4-bit binary register  consists of a group of four flip-flops connected together, and is  capable of storing 4-bit information.

### Types of Binary Registers

Depending on the input and output configurations and data  manipulation, binary registers are classified into the following four  types −

#### Serial-In Serial-Out (SISO) Binary Register

The block diagram of a 4-bit serial-in serial-out (SISO) binary register is depicted in the following figure −

![Serial-In Serial-Out Binary Register](https://www.tutorialspoint.com/digital-electronics/images/serial-in-serial-out-binary-register.jpg)

Here, the output of the first flip-flop is connected to the next  flip-flop. The binary input data will enter the register through the  input line Din. This entry will take place in a serial manner, i.e.  first, the LSB bit will enter the register, then the following bits.

#### Serial-In Parallel-Out (SIPO) Binary Register

The block diagram of a 4-bit serial-in parallel-out (SIPO) binary register is depicted in the following figure.

![Serial-In Parallel-Out Binary Register](https://www.tutorialspoint.com/digital-electronics/images/serial-in-parallel-out-binary-register.jpg)

Here, the data is entered into the register serially, and the output  is taken in parallel form. In this type of binary register, while input  data is being loaded, the output lines remain disabled. Once the process  of data loading is completed, the output lines will become active to  provide the output in parallel form.

#### Parallel-In Serial-Out (PISO) Binary Register

The block diagram of a 4-bit parallel-in serial-out (PISO) binary register is depicted in the following figure

![Parallel-In Serial-Out Binary Register](https://www.tutorialspoint.com/digital-electronics/images/parallel-in-serial-out-binary-register.jpg)

This type of the binary register accepts data in parallel form and  produces results serially. Therefore, in PISO binary register, all bits  of the input data are loaded into the register at the same time. This  register can operate in two modes namely, load mode and shift mode.

In the load mode, the input circuit becomes active to load the input  data bits into the respective flip-flops of the register. In the shift  mode, data bits are shifted from left to right. This results in a  parallel-in serial-out operation.

#### Parallel-In Parallel-Out (PIPO) Binary Register

The block diagram of a 4-bit parallel-in parallel-out binary register is shown in the following figure.

![Parallel-In Parallel-Out Binary Register](https://www.tutorialspoint.com/digital-electronics/images/parallel-in-parallel-out-binary-register.jpg)

This type of binary register receives data in parallel form and  produces output in parallel form. Hence, in PIPO binary register, the  input data bits are loaded into the respective flip-flops at the same  time and the output bits will also appear at the same time.

After getting an overview of binary register and their types, let us now understand the concept of binary register data.

### What is Binary Register Data?

**Binary register** data is nothing but the data and information stored and represented in binary form within a binary register.

In a digital system, the information is represented in the binary  form, i.e. by using a string of 0s and 1s. The binary register can store  these binary information in a series of flip-flops.

The sequence of input and output of the binary register data depends  on the configuration of input and output lines. The amount of binary  register data stored in a binary register depends on the storage  capacity and number of flip-flops in the register. For example, a 16-bit  binary register can store 16 binary digits of binary information.

In a binary register, the stored binary register data can be  manipulating through various operations like writing, retrieving, etc.  Binary registers and binary register data play an important role in any  digital electronic system, such as memory devices, processors, data  centers, communication systems, and more.

In digital systems like computers, calculators, etc., the binary  register data are used to perform various arithmetic and logical  operations.

#### Significance of Binary Register Data

Binary register data plays an important role in the functioning of a  digit electronic system. It serves as a fundamental unit for data  representation in any digital system. It makes the arithmetic and  logical operations straightforward. Binary register data provides faster  data manipulation which increases the data processing speed of a  device.

Overall, binary register and binary register data are fundamental  components of a digital system for performing operations like data  storage, manipulation, retrieval, etc.

### further reading

The Key Idea: Memory with Time Steps A register works over time steps. Think of it like a photo album:

Each moment in time (t) takes a photo of what the register contains The next moment (t+1) shows what happens next
Let's say you have a Bit register and trace through it:

example 01 :

TIME 0 (t=0):
├─ Current stored value = 0
├─ Input (in) = 1
├─ Load signal = 1 (means: STORE this value)
└─ Output (out) = 0 (still shows old value)

TIME 1 (t=1):
├─ Current stored value = 1 (loaded from previous input!)
├─ Input (in) = 0
├─ Load signal = 0 (means: DON'T change, keep current)
└─ Output (out) = 1 (now shows the stored value from t=0)

TIME 2 (t=2):
├─ Current stored value = 1 (unchanged, because load=0)
├─ Input (in) = 1
├─ Load signal = 0 (don't change)
└─ Output (out) = 1 (still 1, unchanged)

TIME 3 (t=3):
├─ Current stored value = 1 (unchanged, because load=0)
├─ Input (in) = 0
├─ Load signal = 1 (NOW load the new value!)
└─ Output (out) = 1 (still shows old value, will update next cycle)

TIME 4 (t=4):
├─ Current stored value = 0 (loaded from t=3 input!)
├─ Input (in) = 0
├─ Load signal = 0
└─ Output (out) = 0 (now the new value appears)

How the parts work together:

┌─────────────────────────────────────┐
│         1-BIT REGISTER              │
│                                     │
│  in ──┐                             │
│       ├─→ [Mux] ──→ [DFF] ──→ out  │
│  load │   (choose)  (store)         │
│       │                             │
│       └─ (feedback: old value)      │
└─────────────────────────────────────┘

The two parts:

Mux (Multiplexer) - The "decision maker":

If load=1: Choose in (new value)
If load=0: Choose feedback (old value)
DFF (Data Flip-Flop) - The "memory":

Stores whatever the Mux gives it
Outputs it the next time step
This is why there's a delay!
Simple analogy:
Imagine a safe with**** a display:

The display shows what's inside (output)
You can put a new value in (input with load=1)
If load=0, the safe keeps what it had
It takes 1 second for the new value to appear on the display

example 02 :

Cycle 0:  DFF contains: 5,  load=1, in=10  →  Output: 5
Cycle 1:  DFF contains: 10, load=0, in=20  →  Output: 10 (stays same!)
Cycle 2:  DFF contains: 10, load=1, in=30  →  Output: 10
Cycle 3:  DFF contains: 30, load=0, in=40  →  Output: 30 (stays same!)

## RAM(8/64/512/4K/16K)

### What is RAM (Random Access Memory)?

RAM (Random Access Memory) is a type of volatile memory that allows data to be read and written in any order. Unlike sequential memory devices, RAM provides direct access to any memory location, making it extremely fast for data retrieval and storage.

In the Nand to Tetris course, we build RAM units hierarchically, starting from individual registers and scaling up to larger memory units.

### RAM Architecture Hierarchy

The RAM units are built in a hierarchical manner:

```
Register (1 word)
    ↓
RAM8 (8 registers)
    ↓
RAM64 (8 × RAM8)
    ↓
RAM512 (8 × RAM64)
    ↓
RAM4K (8 × RAM512)
    ↓
RAM16K (4 × RAM4K)
```

### RAM8 (8 Registers)

**RAM8** is the smallest RAM unit consisting of 8 registers, each storing a 16-bit word.

#### Components:

- **8 registers** for data storage
- **3-bit address** (to select one of 8 registers: 2³ = 8)
- **DMux8Way** (to route input to the correct register)
- **Mux8Way16** (to select output from the correct register)

#### How it works:

1. The 3-bit address selects which register to access
2. If load=1, the input data is written to the selected register
3. The output always shows the content of the addressed register

```
Address Range: 0-7 (000 to 111 in binary)
Storage: 8 words × 16 bits = 128 bits total
```

**Example:**

```
Address = 3 (011), Load = 1, In = 1234
→ Register[3] stores 1234
→ Out = 1234 (after next clock cycle)
```

┌─────────────────────────────────────┐
│  RAM64 (64 registers total)         │
│                                     │
│  ┌──────────────────────────────┐   │
│  │ RAM8[0] (registers 0-7)      │   │
│  │ RAM8[1] (registers 8-15)     │   │
│  │ RAM8[2] (registers 16-23)    │   │
│  │ RAM8[3] (registers 24-31)    │   │
│  │ RAM8[4] (registers 32-39)    │   │
│  │ RAM8[5] (registers 40-47)    │   │
│  │ RAM8[6] (registers 48-55)    │   │
│  │ RAM8[7] (registers 56-63)    │   │
│  └──────────────────────────────┘   │
│           ↑                         │
│        address[3:6]                 │
│        selects RAM8 block           │
└─────────────────────────────────────┘

### RAM64 (64 Registers)

**RAM64** consists of 8 RAM8 units, providing 64 registers total.

#### Components:

- **8 RAM8 units** (each containing 8 registers)
- **6-bit address** (to select one of 64 registers: 2⁶ = 64)
  - First 3 bits select which RAM8 unit (0-7)
  - Last 3 bits select which register within that RAM8 (0-7)
- **DMux8Way** (to route load signal to correct RAM8)
- **Mux8Way16** (to select output from correct RAM8)

#### How it works:

1. Address bits 3-5 (MSB) select which RAM8 unit
2. Address bits 0-2 (LSB) select which register within the RAM8
3. Only the selected RAM8 unit receives the load signal

```
Address Range: 0-63 (000000 to 111111 in binary)
Storage: 64 words × 16 bits = 1024 bits total

Address breakdown:
Bits [5-3]: RAM8 selector (0-7)
Bits [2-0]: Register within RAM8 (0-7)
```

**Example:**

```
Address = 19 (010011)
→ Bits [5-3] = 010 = RAM8 #2
→ Bits [2-0] = 011 = Register #3 within RAM8 #2
```

### RAM512 (512 Registers)

**RAM512** consists of 8 RAM64 units, providing 512 registers total.

#### Components:

- **8 RAM64 units** (each containing 64 registers)
- **9-bit address** (to select one of 512 registers: 2⁹ = 512)
  - First 3 bits select which RAM64 unit (0-7)
  - Last 6 bits select which register within that RAM64 (0-63)
- **DMux8Way** (to route load signal to correct RAM64)
- **Mux8Way16** (to select output from correct RAM64)

#### How it works:

1. Address bits 6-8 (MSB) select which RAM64 unit
2. Address bits 0-5 (LSB) are passed to the selected RAM64

```
Address Range: 0-511 (000000000 to 111111111 in binary)
Storage: 512 words × 16 bits = 8192 bits = 8 Kbits

Address breakdown:
Bits [8-6]: RAM64 selector (0-7)
Bits [5-0]: Register within RAM64 (0-63)
```

**Example:**

```
Address = 325 (101000101)
→ Bits [8-6] = 101 = RAM64 #5
→ Bits [5-0] = 000101 = Register #5 within RAM64 #5
```

### RAM4K (4096 Registers)

**RAM4K** consists of 8 RAM512 units, providing 4096 registers total (4K).

#### Components:

- **8 RAM512 units** (each containing 512 registers)
- **12-bit address** (to select one of 4096 registers: 2¹² = 4096)
  - First 3 bits select which RAM512 unit (0-7)
  - Last 9 bits select which register within that RAM512 (0-511)
- **DMux8Way** (to route load signal to correct RAM512)
- **Mux8Way16** (to select output from correct RAM512)

#### How it works:

1. Address bits 9-11 (MSB) select which RAM512 unit
2. Address bits 0-8 (LSB) are passed to the selected RAM512

```
Address Range: 0-4095 (000000000000 to 111111111111 in binary)
Storage: 4096 words × 16 bits = 65536 bits = 64 Kbits

Address breakdown:
Bits [11-9]: RAM512 selector (0-7)
Bits [8-0]: Register within RAM512 (0-511)
```

**Example:**

```
Address = 2050 (100000000010)
→ Bits [11-9] = 100 = RAM512 #4
→ Bits [8-0] = 000000010 = Register #2 within RAM512 #4
```

### RAM16K (16384 Registers)

**RAM16K** consists of 4 RAM4K units, providing 16384 registers total (16K).

#### Components:

- **4 RAM4K units** (each containing 4096 registers)
- **14-bit address** (to select one of 16384 registers: 2¹⁴ = 16384)
  - First 2 bits select which RAM4K unit (0-3)
  - Last 12 bits select which register within that RAM4K (0-4095)
- **DMux4Way** (to route load signal to correct RAM4K)
- **Mux4Way16** (to select output from correct RAM4K)

#### How it works:

1. Address bits 12-13 (MSB) select which RAM4K unit
2. Address bits 0-11 (LSB) are passed to the selected RAM4K

```
Address Range: 0-16383 (00000000000000 to 11111111111111 in binary)
Storage: 16384 words × 16 bits = 262144 bits = 256 Kbits = 32 KB

Address breakdown:
Bits [13-12]: RAM4K selector (0-3)
Bits [11-0]: Register within RAM4K (0-4095)
```

**Example:**

```
Address = 10000 (10011100010000)
→ Bits [13-12] = 10 = RAM4K #2
→ Bits [11-0] = 011100010000 = Register #1808 within RAM4K #2
```

### Key Concepts Across All RAM Units

#### 1. Address Decoding

Each RAM unit uses part of the address to select a sub-unit and passes the remaining bits down the hierarchy.

#### 2. Load Signal Distribution

The load signal is only sent to the selected sub-unit using a DMux, preventing unwanted writes.

#### 3. Output Multiplexing

All sub-units output their values, but a Mux selects only the output from the addressed unit.

#### 4. Hierarchical Design Pattern

```
RAMn consists of k RAMm units where:
- n = k × m
- Address bits = log₂(k) + (address bits of RAMm)
```

### Comparison Table


| RAM Unit | # Registers | Address Bits | Sub-units   | Structure     |
| -------- | ----------- | ------------ | ----------- | ------------- |
| RAM8     | 8           | 3            | 8 Registers | 8 × Register |
| RAM64    | 64          | 6            | 8 RAM8      | 8 × RAM8     |
| RAM512   | 512         | 9            | 8 RAM64     | 8 × RAM64    |
| RAM4K    | 4096        | 12           | 8 RAM512    | 8 × RAM512   |
| RAM16K   | 16384       | 14           | 4 RAM4K     | 4 × RAM4K    |

### Timing Behavior

All RAM units follow the same timing pattern:

```
Time t:   Address = A, Load = 1, In = V
          Out = old value at address A

Time t+1: The register at address A now contains V
          Out = V (if still addressing A)
```

The write operation takes one clock cycle to complete, just like the basic register.

### Why This Hierarchy Matters

1. **Modularity**: Each RAM unit is built from smaller, already-tested units
2. **Scalability**: Easy to create larger memories by following the pattern
3. **Efficiency**: Hierarchical addressing is faster than scanning all registers
4. **Real-world**: Modern computer memory uses similar hierarchical structures

This hierarchical approach demonstrates how complex systems (16K words of memory) can be built from simple components (flip-flops) through systematic, layered design.


## Program Counter

i didnt find quit a good documntation for program counter but this youtube video saved which made it very easy and made me feel really dumb

- [youtube.com](https://www.youtube.com/watch?v=ccf9ngGIb8c)

How PC is Built (Implementation):

The PC needs to support 4 operations on the same value. Here's how it works internally:

Inc16 - Adds 1 to the current PC value
Mux chips - Select between: reset (0), load (new value), or increment
Register - Stores the selected value and outputs it
```
┌─────────────────────────────────────┐
│  Current PC value (from Register)   │
└──────────┬──────────────────────────┘
           │
      ┌────▼────┐
      │  Inc16   │ ──► PC + 1
      └────┬────┘
           │
    ┌──────▼──────┐
    │  Mux logic  │
    │  (4 inputs) │
    └──────┬──────┘
      inc/load/reset signals
           │
      ┌────▼────────┐
      │  Register   │ ──► Output PC
      └─────────────┘
```

### Relationship with Other Chips:

1. Relationship with RAM (Instruction Memory)

PC is the address selector for RAM
PC outputs an address → RAM uses that address to fetch the instruction
When PC = 5, RAM outputs instruction at address 5
PC (output) ──address[14]──► RAM16K
                              │
                              └──► Instruction at PC location

### 2. Relationship with Inc16 (Arithmetic)

PC uses Inc16 to increment its value
Inc16 takes current PC + 1 and gives the next instruction address

PC ──in──► Inc16 ──out(PC+1)──► back to Mux

### 3. Relationship with Register (Storage)

PC is a 16-bit Register
The Register stores the current program counter value
At each clock tick, the Register updates based on control signals

Register = PC (but u can say its like special register )

### 4. Relationship with Mux (Selection Logic)

PC uses Mux to choose between:
0 (reset)
in[16] (load - jump)
PC + 1 (increment - normal flow)
PC (hold - stay same)

     ┌─── 0 ────┐
     │           │
  in[16] ──► Mux ──► Register ──► PC
     │           │
 (PC+1) ────────┘
     │
  (PC) ─────────┘

### Real CPU Execution Flow:

Let's say we're fetching and executing instructions:
Clock Cycle 1:
┌──────────────────────────────────────┐
│ PC = 0                               │
├──────────────────────────────────────┤
│ PC (0) ──address──► RAM ──► Fetch instruction at address 0
│ Execute instruction 0
│ Set inc=1 to prepare for next
└──────────────────────────────────────┘

Clock Cycle 2:
┌──────────────────────────────────────┐
│ PC incremented to 1 (Inc16 worked)   │
├──────────────────────────────────────┤
│ PC (1) ──address──► RAM ──► Fetch instruction at address 1
│ Execute instruction 1
│ Set inc=1 again
└──────────────────────────────────────┘

Clock Cycle 3:
┌──────────────────────────────────────┐
│ PC incremented to 2                  │
├──────────────────────────────────────┤
│ PC (2) ──address──► RAM ──► Fetch instruction at address 2
│ But instruction 2 is a JUMP to 100
│ Set load=1, in=100
└──────────────────────────────────────┘

Clock Cycle 4:
┌──────────────────────────────────────┐
│ PC loaded with 100 (jumped!)         │
├──────────────────────────────────────┤
│ PC (100) ──address──► RAM ──► Fetch instruction at address 100
│ Execute instruction 100
│ Set inc=1
└──────────────────────────────────────┘

### PC's Role in the Full CPU:
┌─────────────────────────────────────────────────────┐
│              CPU (Hack Computer)                     │
│                                                      │
│  ┌──────────┐         ┌─────────────┐               │
│  │    PC    │────────►│  RAM16K     │               │
│  │          │ address │(Instruction │               │
│  └────▲─────┘         │  Memory)    │               │
│       │                │             │               │
│       │ jump signal    └────────┬────┘               │
│       │                         │                    │
│       │              ┌──────────▼──────┐             │
│       │              │  Control Unit   │             │
│       │              │ (Decodes instr.)│             │
│       │              └────────┬────────┘             │
│       │                       │                      │
│       │                    ┌──▼──┐                  │
│       └────────────────────│ ALU │                  │
│         (next addr)        └─────┘                  │
│                                                      │
└─────────────────────────────────────────────────────┘

### In summary:

PC keeps track of execution position
RAM uses PC to fetch the current instruction
Control Unit decodes instruction and may tell PC to jump
Inc16 helps PC move to the next instruction
This cycle repeats creating the program flow

## Program Counter (PC)

A **Program Counter** is a 16-bit register that keeps track of which instruction the CPU should execute next. It's the "brain's memory" of program position.

### PC Behavior

The PC responds to 4 control signals with the following priority:

| Signal | Behavior | Example |
|--------|----------|---------|
| **reset** | Set PC to 0 (restart program) | `reset=1` → PC = 0 |
| **load** | Load a specific address (jump) | `load=1, in=100` → PC = 100 |
| **inc** | Increment by 1 (next instruction) | `inc=1` → PC = PC + 1 |
| **none** | Hold current value | All 0 → PC unchanged |

### PC Logic Priority

```
if reset == 1:
    out = 0
else if load == 1:
    out = in[16]
else if inc == 1:
    out = out + 1
else:
    out = out (no change)
```

### How PC Works Internally

```
┌─────────────────────────────────────────────────┐
│  Current PC Value (Stored in Register)          │
└────────────────────┬────────────────────────────┘
                     │
             ┌───────▼────────┐
             │     Inc16      │
             │  (adds 1)      │
             └───────┬────────┘
                     │
        ┌────────────▼────────────┐
        │   Mux4Way Selection     │
        │  (Choose 1 of 4 paths)  │
        └────────────┬────────────┘
                     │
    ┌────────┬───────┼───────┬──────────┐
    │        │       │       │          │
   (0)   (in)   (PC+1)    (PC)    Control
                               (reset/load/inc)
                     │
             ┌───────▼────────┐
             │   Register     │
             │  (Storage)     │
             └───────┬────────┘
                     │
              Output PC → to CPU
```

### PC Relationships with Other Chips

#### 1. **PC ↔ RAM16K (Instruction Fetching)**
```
PC Output (address[14])
         ↓
    ┌─────────────┐
    │  RAM16K     │
    │  (Program   │
    │   Memory)   │
    └─────────────┘
         ↓
  Instruction @ PC address
```
- PC provides the address
- RAM16K outputs the instruction at that address

#### 2. **PC ↔ Inc16 (Increment Logic)**
```
PC Value ──►┌─────────┐
            │  Inc16  │ ──► PC + 1
            └─────────┘
                ↓
          (Feeds back to Mux)
```
- Inc16 adds 1 to current PC
- Used for sequential instruction execution

#### 3. **PC ↔ Register (Storage)**
```
PC IS a 16-bit Register
```
- PC is fundamentally a Register chip
- Stores the current program address
- Updates on each clock cycle based on control signals

#### 4. **PC ↔ Mux4Way (Control Routing)**
```
Inputs to Mux4Way:
  a=0          (reset path)
  b=in[16]     (load/jump path)
  c=PC+1       (increment path)
  d=PC         (hold path)
        ↓
  sel={reset, load, inc}
        ↓
  Output → Register → PC
```

### PC in the Full CPU Architecture

```
┌────────────────────────────────────────────────────┐
│              CPU (Hack Computer)                    │
│                                                     │
│  ┌────────────┐          ┌──────────────┐          │
│  │     PC     │ address  │   RAM16K     │          │
│  │ (Program   │─────────►│ (Instructions)│          │
│  │ Counter)   │          │              │          │
│  └─────▲──────┘          └────────┬─────┘          │
│        │                          │                 │
│        │                    ┌─────▼─────┐          │
│        │                    │ Decoder/   │          │
│        │                    │ Control    │          │
│        │                    │ Unit       │          │
│        │                    └─────┬─────┘          │
│        │                          │                 │
│        │                    ┌─────▼──────┐         │
│        │                    │    ALU      │         │
│        │                    │ (Execution) │         │
│        │                    └─────┬──────┘         │
│        │                          │                 │
│        └──────(jump signal)───────┘                 │
│           (reset/load/inc)                          │
│                                                     │
└────────────────────────────────────────────────────┘
```

### Execution Flow Example

**Cycle 1:** PC=0 → RAM outputs instruction 0 → set inc=1  
**Cycle 2:** PC=1 → RAM outputs instruction 1 → set inc=1  
**Cycle 3:** PC=2 → RAM outputs instruction 2 (JUMP to 100) → set load=1, in=100  
**Cycle 4:** PC=100 → RAM outputs instruction 100 → set inc=1  

This cycle repeats continuously, executing the program sequentially or jumping as needed.

## Resources :

- [link01](https://cs.nyu.edu/~gottlieb/courses/2000s/2001-02-fall/arch/lectures/lecture-05.html)
- [watson](http://watson.latech.edu/book/circuits/circuitsSequential1.html)
- [geekforgeeks](https://www.geeksforgeeks.org/digital-logic/shift-registers-in-digital-logic/)
