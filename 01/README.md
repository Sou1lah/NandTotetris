# Project One — Nand2Tetris: Logic Gates

**Status:** In progress / Implemented

## Overview
This repository contains HDL implementations for Project 1 of the Nand2Tetris curriculum. The work focuses on constructing correct combinational logic components (basic gates, multiplexers, demultiplexers) and extending them to 16-bit buses and multi-way variants using HDL. Emphasis is placed on modular design, test-driven verification, and composing complex behavior from simpler building blocks.

## Files Included
- `And.hdl` — 1-bit AND gate
- `And16.hdl` — 16-bit AND (bitwise application of `And`)
- `Not.hdl` — 1-bit NOT gate
- `Not16.hdl` — 16-bit NOT
- `Or.hdl` — 1-bit OR gate
- `Or16.hdl` — 16-bit OR
- `Or8Way.hdl` — reduction OR across 8 inputs
- `Xor.hdl` — 1-bit XOR gate
- `Mux.hdl` — 1-bit selector (two-way)
- `Mux16.hdl` — 16-bit two-way multiplexer
- `Mux4Way16.hdl` — 4-way 16-bit multiplexer
- `Mux8Way16.hdl` — 8-way 16-bit multiplexer
- `DMux.hdl` — 1-bit demultiplexer (single input to two outputs)
- `DMux4Way.hdl` — 4-way demultiplexer
- `DMux8Way.hdl` — 8-way demultiplexer

## Component reference: purpose and truth tables
This section lists each component, a short description of what it is used for, and the truth table(s) you can use to verify it.

### 1-bit primitives

**`And`** — Purpose: logical conjunction; used where two signals must both be true.
Typical uses in Nand2Tetris: bitwise AND operation in the ALU, carry-generation in adders, masking bits, and combining control conditions.

A | B | Out
--|---|----
0 | 0 | 0
0 | 1 | 0
1 | 0 | 0
1 | 1 | 1

**`Or`** — Purpose: logical disjunction; used where at least one signal should be true.
Typical uses in Nand2Tetris: bitwise OR operation in the ALU, combining conditions (e.g., to detect if any input bit is set), and forming logic for control signals.

A | B | Out
--|---|----
0 | 0 | 0
0 | 1 | 1
1 | 0 | 1
1 | 1 | 1

**`Not`** — Purpose: logical inversion; used to negate control or data signals.
Typical uses in Nand2Tetris: implementing logical negation in ALU control, inverting signals for two's-complement subtraction, and deriving complementary control lines.

A | Out
--|----
0 | 1
1 | 0

**`Xor`** — Purpose: true when inputs differ; used in parity and arithmetic logic.
Typical uses in Nand2Tetris: computing the sum bit in adders (half- and full-adder logic), parity checks, and equality/inequality tests.

A | B | Out
--|---|----
0 | 0 | 0
0 | 1 | 1
1 | 0 | 1
1 | 1 | 0


### Multi-bit and reduction components

**`And16`, `Or16`, `Not16`** — Purpose: apply the corresponding 1-bit operation independently to each bit of a 16-bit bus. Tests should verify representative bit patterns (all zeros, all ones, alternating bits, single-bit set).

Behavior (per-bit): For each bit i, Out[i] = Gate(A[i], B[i]) (or Out[i] = Not(A[i]) for `Not16`).

**`Or8Way`** — Purpose: reduction OR of eight inputs; outputs 1 if any input is 1.

i0 i1 i2 i3 i4 i5 i6 i7 | Out
------------------------|----
all 0                   | 0
any 1                   | 1


### Multiplexers

**`Mux` (1-bit 2-way)** — Purpose: select between two inputs `a` and `b` using select `sel`.

sel | a | b | Out
----|---|---|----
0   | 0 | 0 | 0
0   | 0 | 1 | 0
0   | 1 | 0 | 1
0   | 1 | 1 | 1
1   | 0 | 0 | 0
1   | 0 | 1 | 1
1   | 1 | 0 | 0
1   | 1 | 1 | 1

**`Mux16`** — Purpose: 16-bit two-way multiplexer; applies `Mux` independently to each bit of the buses.

**`Mux4Way16` / `Mux8Way16`** — Purpose: multi-way 16-bit multiplexers; select lines encode which input bus is forwarded to the output.

Selection mapping examples:
- `Mux4Way16` (select is 2 bits `s1 s0`): `00`→input0, `01`→input1, `10`→input2, `11`→input3.
- `Mux8Way16` (select is 3 bits `s2 s1 s0`): `000`→input0, ..., `111`→input7.


### Demultiplexers

**`DMux` (1-bit 2-way)** — Purpose: route a single input `in` to one of two outputs `a` or `b` according to `sel`.

sel | in | a | b
----|----|---|---
0   | 0  | 0 | 0
0   | 1  | 1 | 0
1   | 0  | 0 | 0
1   | 1  | 0 | 1

**`DMux4Way` / `DMux8Way`** — Purpose: route a single input to one of 4 or 8 outputs based on multi-bit select lines. Only the selected output should carry the input value; all others must be 0.

Selection mapping (example for `DMux4Way` with two-bit select): `00`→out0, `01`→out1, `10`→out2, `11`→out3.


## How to run / test
1. Launch the Hardware Simulator provided with the Nand2Tetris tools.
2. Load a `.hdl` file and run its corresponding `.tst` script (if available) or provide manual test vectors.
3. Verify outputs against the truth tables above and inspect waveforms to confirm signal routing.

## Next steps / TODO
- Add or complete `.tst` test scripts for any components that lack them.
- Add example test cases and a short usage guide demonstrating typical test vectors.
- Optionally document waveform examples or include screenshots to aid debugging.

## Resources
- https://nand2tetris-hdl.github.io/?utm_source=chatgpt.com#not16