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

## RAM(8/64/512/4K/16K)


In **Section 12.4**  we talked about how a sequential device as simple as an R-S flip-flop  could be used to remember one bit of data. We now develop a complete  memory cell, called a binary cell, based on the flip-flop. When such a  cell is selected and in “read” mode, the current value of its underlying  flip-flop will be transferred to the cell’s output line. When the cell  is selected and in “write” mode, an input data signal will determine the  value remembered by the flip-flop. A complete circuit is shown in **Figure 12.34**.

  The fundamental design of this binary cell is based on the R-S flip-flop of **Figure 12.23**  though there are some significant differences. To begin with, the cell  has three inputs and a single output. The inputs are labeled “Select”,  “Read/write”, and “Input”. The output line is labeled “Output”.

![](http://watson.latech.edu/book/circuits/images/watsonvmdetail.png)

**Figure 12.34:** A Binary cell (BC) for RAM memory

The “select” input is used to access the cell, either for  reading or writing. When the select line is high, “1”, then a memory  operation can be performed on this cell. When the select line of the  binary cell is low, “0”, then the contents of the cell are not currently  of interest – i.e., at the present time the cell is not being read from  or written to. We can see how “select” is given this power by noting  that both the inputs and the output of the underlying R-S flip-flop are  routed through**and**gates and that  “select” is one of the inputs to each of these gates. Thus, if “select”  is low, the inputs to the R-S flip-flop will stay low (meaning that its  stored value will not change) and the output produced by the cell will  be low (regardless of whether the actual bit held in the flip-flop is  “0” or “1”).

  The next input we’ll examine is “Read/write”. A system clock will  drive this input. As was the case with the clocked R-S flip-flop of **Figure 12.31**,  a low, “0”, will signify “read” while a high, “1”, will signify  “write”. During the read phase it will not be possible to write to the  cell. Likewise, during the write phase it will not be possible to read  the contents of the cell.

Assume the cell has been selected (i.e., “select” is high  signifying that a memory access operation is to be performed on this  cell.)  Furthermore, assume that the clock value on the “Read/write”  line is low (forcing the “negated Read/write” to high) indicating the  cell contents are to be read. In this case, the value output by the cell  will depend solely on the Q value of the flip-flop. If Q is low, the  cell outputs a “0”, if Q is high, the cell outputs a “1”. This is  because the**and**gate attached to  the cell’s output line has three inputs: “select”, “negated Read/write”,  and Q; and both “select” and “negated Read/write” are currently high.

As mentioned earlier, when the cell is being read its contents  cannot be modified. The reason for this is that the same low value on  the “Read/write” line that allows the cell to be read, is fed into the**and**gates  guarding the inputs to the flip-flop. Thus during reads, the inputs to R  and S are guaranteed to be low preventing the value of the flip-flop  from being modified.

  When the cell is selected and the “Read/write” line is set to high,  signifying a “write” operation, the value placed into the cell will  depend solely on the state of the “Input” line.

The reason for this is that the**and**gates  that guard the R and S inputs of the flip-flop will both have two of  their inputs set high: the “select” and “Read/write” inputs. Thus, if  “Input” is high, S (set) will receive a high and the flip-flop will  store a “1”. If, on the other hand, “Input” is low, then R (reset) which  receives a negated version of “Input” will go high and the flip-flop  will reset to “0”. Note that having a negated version of the input line  run into R is a clever idea, since it prevents the R-S flip-flop from  ever entering into its invalid state. (Recall from our discussion of R-S  flip-flops in **Section 12.4** that if R and S are ever set to “1” at the same time the flip-flop enters a stable, but invalid state.)

![](http://watson.latech.edu/book/circuits/images/addandalu.png)

**Figure 12.35:** A Binary Cell – encapsulated view

It is worth mentioning that during write operations, reading is prohibited. This is easy to see, since the**and**gate  guarding the “Output” line receives one of its inputs from “negated  Read/write” which is held low during write operations. Hence, output  from the cell will always be low, “0”, during writes, regardless of the  actual value on the Q line.

**Figure 12.35** contains an  encapsulated view of a single binary cell. An entire random access  memory (RAM) can be constructed from a large collection of binary cells,  together with some address decoding circuitry. The Watson Virtual  Machine includes a memory of 256 words, each 16 bits wide – much too  large to be conveniently illustrated.[[4]](http://watson.latech.edu/book/circuits/circuitsMicrocomputer3.html#ftn4) In order to have a manageable circuit diagram, **Figure 12.36** presents an implementation of a 4 x 2 RAM. Such a RAM module has four separate “words” of memory, each two bits wide.

  A word of storage will consist of two binary cells arranged in such a  way that both bits can be accessed simultaneously. Because the memory  consists of four of these words, a total of eight binary cells will be  used. These cells will be laid out according to a four row by two column  grid pattern, where each row of the grid represents one word.

Examining the inputs to the memory unit, we see that there are two input data lines at the top of the diagram (D**1**and D**0**),  representing the two bits of the number to be written. One of these  bits will be the high-order data bit and one the low. The signal from  the high-order data input line is fed to the high-order bit of every  word. Likewise, the low-order data input signal is fed to the low-order  bit of every word.

On the left side of the circuit diagram, a two-bit address (A**1**and A**0**)  is input. This address is fed into a two-to-four decoder that generates  a high signal down the data line corresponding to the word of memory to  be accessed (either read or written).  The decoder also accepts an  “enable” input. This input essentially tells the decoder whether the bit  pattern currently on the input address lines is a valid memory address  that is to be decoded, or whether the circuit should just ignore this  bit pattern for the moment.

![](http://watson.latech.edu/book/circuits/images/binaryram.png)

**Figure 12.36:** A 4 x 2 RAM memory

			The final input is the clock signal that the memory unit receives  via the read/write line. Note that this signal is propagated to every  binary cell in the entire RAM, allowing the memory unit to either read  from or write to any of the binary cells. 		
Two output lines are visible at the bottom of the circuit (Z**1**and Z**0**);  one for the high-order bit of the number to be output, one for the  low-order bit. As you can see, the output lines from each of the four  binary cells making up a column are fed into a multi-input**or**gate  that is tied to the output line for that column. So, if any of the  binary cells in a column produces a “1”, then that column’s output line  will produce a “1” as well. Due to the presence of the address decoder,  however, we can be sure that only one row, and thus only one bit per  column, can be accessed (either read or written) at any point in time.

We now come to the close of our discussion concerning the  implementation of main memory, and thus to the end of this book’s  material on computer “hardware”. As I am sure you can appreciate, we  have just scratched the surface of this fascinating field. However, my  hope is that this brief introduction to digital logic has convinced you  that computers can be completely understood in terms of large networks  of very simple logic gates that are interconnected in complex patterns.
