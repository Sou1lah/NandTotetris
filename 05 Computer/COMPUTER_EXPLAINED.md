## Hack CPU Architecture (Project 5)

### Diagram

```mermaid
flowchart TD
    INSTRUCTION[Instruction]
    INM[inM]
    RESET[reset]
    ORA[Or (A-instr or destA)]
    ANDA[And (C-instr & destA)]
    ANDD[And (C-instr & destD)]
    ANDM[And (C-instr & destM)]
    MUXIN[Mux16 (A/ALU)]
    AREG[ARegister]
    MUXA[Mux16 (A/M)]
    DREG[DRegister]
    ALU[ALU]
    OUTM[outM]
    WRITEM[writeM]
    ADDRESSM[addressM]
    PC[PC]
    PCOUT[pc]

    INSTRUCTION --> ORA
    INSTRUCTION --> ANDA
    INSTRUCTION --> ANDD
    INSTRUCTION --> ANDM
    INSTRUCTION --> MUXIN
    INSTRUCTION --> MUXA
    INSTRUCTION --> ALU
    INSTRUCTION --> PC
    INM --> MUXA

    ORA --> AREG
    ANDA --> MUXIN
    MUXIN --> AREG
    AREG --> MUXA
    AREG --> ADDRESSM

    ANDD --> DREG
    ALU --> DREG
    DREG --> ALU

    MUXA --> ALU
    ALU --> OUTM
    ALU --> MUXIN
    ALU --> DREG

    ANDM --> WRITEM

    ALU --> PC
    PC --> PCOUT

    RESET --> PC
```

### Explanation

- **Instruction**: The 16-bit instruction input is decoded to control the CPU's operation. Bit 15 distinguishes between A- and C-instructions.
- **ARegister & DRegister**: Store values for computation and addressing. The A register can hold an address or a value; the D register is for data.
- **Mux16 (A/M)**: Selects between the A register and inM (RAM[A]) as the ALU's y input, based on the instruction's a-bit.
- **ALU**: Performs arithmetic and logic operations as specified by the instruction's control bits.
- **outM**: The result from the ALU, sent to memory if writeM is asserted.
- **addressM**: The address for memory access, always the lower 15 bits of the A register.
- **writeM**: Asserted if the instruction specifies writing to memory (M).
- **PC (Program Counter)**: Holds the address of the next instruction. It can increment, load a new value (for jumps), or reset.
- **Jump Logic**: Decodes the jump bits and ALU output to determine if the PC should jump to the address in the A register.

This architecture allows the CPU to fetch, decode, and execute Hack machine instructions, supporting computation, memory access, and program control (jumps and branches).