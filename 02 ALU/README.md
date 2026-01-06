## ALU (Arithmetic Logic Unit)

Arithmetic Logic Unit abbreviated as ALU is considered as the engine or  heart of every central processing unit (CPU). ALU is basically a  combination logic circuit that can perform arithmetic and logical  operation on digital data (data in binary format). It can also execute  instructions given to a computing system like a digital computer

![](https://www.tutorialspoint.com/digital-electronics/images/arithmetic-logic-unit.jpg)

### Features of Arithmetic Logic Unit

* The ALU can perform all arithmetic and logic operations such as  addition, subtraction, multiplication, division, logical comparisons,  etc.
* It can also perform bitwise and mathematical operations on binary numbers.
* It contains two segments namely, AU (**arithmetic unit**) and LU (**logic unit**) to perform arithmetic operations and logical operations respectively.
* It is the computational powerhouse within a central processing unit (CPU).
* ALU is the part of every CPU where actual data processing takes place.
* ALU is responsible for interpreting the code instructions based on which operations to be performed on the input data.
* Once the data processing is completed, the ALU sends the outcomes to the memory unit or output unit.

### Main Components of Arithmetic Logic Unit

The arithmetic logic unit consists of various functional parts that  are responsible for performing specific operations like addition,  subtraction, multiplication, division, comparison, and more. Some of the  key components of the arithmetic logic unit are explained below −

#### Arithmetic Unit

The main components used in the arithmetic unit (AU) segment of the arithmetic logic unit are as follows −

#### Adder

The adder or binary adder is one of the important components of the  arithmetic logic unit. It performs the addition of two or more binary  numbers. To accomplish this operation, it performs a series of logical  and arithmetic operations. Some common types of adders used in the  arithmetic ogic unit are half-adder, full-adder, parallel adder, and  ripple carry adder. Each type of adder is designed and optimized to  perform a specific computing operation.

#### Subtractor

The subtractor is another digital combinational circuit designed to  perform subtraction of binary numbers. In most arithmetic logic unit,  the subtractor uses 2s complement arithmetic to perform subtraction on  binary numbers.

#### Multiplier and Divider

In more complex and advanced arithmetic logic units, dedicated  multiplier and divider circuits are also implemented to perform  multiplication and division on binary numbers. These circuits use  advanced processing techniques like iterative or parallel processing to  accomplish these operations.

### Logic Unit

The logic unit (LU) of the ALU comprises the components responsible  for performing Boolean or comparison operations. The following are some  main components of the logic unit of an ALU −

#### Logic Gates

The logic gates like AND, OR, NOT, NAND, NOR, XOR, and XNOR are the  key components of logic unit. These are standard logic circuits that can  manipulate input data based on some predefined logical instructions and  generate a desired output.

Each logic gate can perform a specific logical operation. However,  different types of logic gates can be connected together in a specific  manner to perform complex logical operations.

#### Type of Logic Gate

The brief overview of each  type of logic gate is explained here −

* **AND Gate** − It performs the Boolean multiplication on input binary  data. Its output is logic 1 or true, only when all its inputs are logic  1 or true.
* **OR Gate** − The OR gate performs the Boolean addition of input  binary data. It generates a logic 1 or true output, if any of its inputs  is logic 1 or true.
* **NOR Gate** − The NOT gate performs the inversion operation. It  gives a logic 1 or true output when its input is logic 0 or false and  vice-versa.
* **NAND Gate** − The NAND gate performs the NOTed AND operation and  produces a logic 1 or true output when both inputs or any of the inputs  is logic 0 or false.
* **NOR Gate** − The NOR gate performs the NOTed OR operation and generates a logic 1 or true output when all its inputs are logic 0 or false.
* **XOR Gate** − The XOR gate performs the exclusive OR operation and  produces a logic 1 or true output when its both inputs are dissimilar.  Hence, it is used as inequality detector.
* **XNOR Gate** − The XNOR gate performs the exclusive NOR operation  and gives a logic 1 or true output when both its inputs are similar.  Thus, it is used as an equality detector.

This is all about structure and components of the arithmetic logic  unit. Let us now understand what functions an ALU can perform.

### Functions of Arithmetic Logic Unit

The arithmetic logic unit can perform a wide range of functions and  operations in digital computing systems. Some important functions that  an arithmetic logic unit perform are explained below −

#### Arithmetic Operations

The arithmetic operations are one of the primary functions that the  arithmetic logic unit performs. This category of operations includes  addition, subtraction, multiplication, and division of binary numbers.  All these operations form the basis of mathematical computations that  the arithmetic logic unit can perform.

#### Logical Operations

The arithmetic logic unit can also perform various logical operations  such as AND operation, OR operation, NOT operation, etc. These logical  operations form the basis of decision making and data manipulation  processes.

#### Comparison Operations

The arithmetic logic unit also facilitates to perform various  comparison operations such as equal to, not equal to, less than, greater  than, etc. These comparison operations are essential in decision making  processes.

#### Shift Operations

The arithmetic logic unit can also perform shift operations on binary  numbers such as left shift and right shift. These operations are  important in multiplication and division operations. The shift  operations can manipulate binary data at bit level and hence optimize  the arithmetic calculations.

### Working of Arithmetic Logic Unit

The working of the arithmetic logic unit depends on a combination of  input data and control signals. In other words, the arithmetic logic  unit receives the input data and control signals and then interpret  these data and signals to perform specific operations.

Let us understand the working of the arithmetic logic unit in detail by breaking it down in sub-components.

#### Receiving Input Data and Control Signals

The arithmetic logic unit receives the input data from the user and a  set of control signals that specifies the operation to be performed.  The data is received through the input data path while the control  signals are received from the control unit.

#### Execution of Operation

Once the arithmetic logic unit received the input data and control  signals, it selects an appropriate functional component among arithmetic  unit, logic unit, comparison unit, or shift unit to perform the  specific operation. Once the operation completes, the ALU sends the  results to the memory unit for storage or output unit.

## Half-Adder

A combinational logic circuit which is designed to add two binary digits is called as a **half adder**.  The half adder provides the output along with a carry value (if any).  The half adder circuit is designed by connecting an EX-OR gate and one  AND gate. It has two input terminals and two output terminals for sum  and carry. The block diagram and circuit diagram of a half adder are  shown below

![](https://www.tutorialspoint.com/digital-electronics/images/half-adder-block-diagram.jpg)

### Operation of Half Adder

Half adder adds two binary digits according to the rules of binary addition. These rules are as follows −

$0+0=0$
$0+1=1$
$1+0=1$
$1+1=10$ Sum=0 & Carry=1

### Truth Table of Half Adder

![](/assets/Halfaddertable.png)

## Full Adder

A combinational logic circuit that can add two binary digits (bits)  and a carry bit, and produces a sum bit and a carry bit as output is  known as a **full-adder**.

In other words, a combinational circuit which is designed to add  three binary digits and produces two outputs (sum and carry) is known as  a full adder. Thus, a full adder circuit adds three binary digits,  where two are the inputs and one is the carry forwarded from the  previous addition. The block diagram and circuit diagram of the full  adder are shown below

![](https://www.tutorialspoint.com/digital-electronics/images/full-adder-block-diagram.jpg)

### Operation of Full Adder

Full adder takes three inputs namely A, B, and C~in~. Where, A and B are the two binary digits, and C~in~  is the carry bit from the previous stage of binary addition. The sum  output of the full adder is obtained by XORing the bits A, B, and C~in~. While the carry output bit (C~out~) is obtained using AND and OR operations

### Advantages of Full Adder

The following are the important advantages of full adder over half adder −

* Full adder provides facility to add the carry from the previous stage.
* The power consumed by the full adder is relatively less as compared to half adder.
* Full adder can be easily converted into a half subtractor just by adding a NOT gate in the circuit.
* Full adder produces higher output that half adder.
* Full adder is one of the essential part of critic digital circuits like multiplexers.
* Full adder performs operation at higher speed.

### Applications of Full Adder

The following are the important applications of full adder −

* Full adders are used in ALUs (arithmetic logic units) of CPUs of computers.
* Full adders are used in calculators.
* Full adders also help in carrying out multiplication of binary numbers.
* Full adders are also used to realize critic digital circuits like multiplexers.
* Full adders are used to generate memory addresses.
* Full adders are also used in generation of program counterpoints.
* Full adders are also used in GPU (Graphical Processing Unit).
