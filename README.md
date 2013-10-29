atoc
----

Short for Ato-Computer, the atoc machine is designed to be as small as possible while retaining simplicity. It is intended to be easy to understand while also being easy to implement. An end goal is the atoc's implementation in 7400 logic. 

### Specification ###
The atoc is an 8-bit architecture. However, due to the way that the instruction set is implemented the actual length of the registers and resulting address space is unlimited. For ease of implementation and proof of concept, the current design uses 12 bit addresses with registers 12 bits long. It should be noted that the arithmetic instructions only affect the lower 8 bits of the value with propogating carry. 

The architecture has 4 general purpose registers. Each is as long as an address, or in this implementation 12 bits. 
- a
- b/x
- c/sp
- pc

The only implicit register usage occurs with the program counter, or register 3, which is used for fetching the next instruction each cycle.

The ALU supports 4 basic operations.
- and
- xor
- add
- sub

The left operand is 12 bits long, while the right operand is only 8. Bitwise operations keep the top 4 bits, while addition and subtraction can propogate a carry. The ALU is also used internally for incrementing and registers implicitly.

The architecture also contains a temporary register, named dd, for storing 12 bit entities temporarily. It also acts as the data register for memory acces. It can be used in parallel with the ALU, allowing a memory load and increment to be performed simultaneously.

Condition branching is implemented with the conditional opcode. This checks the condition code against either zero, not zero, positive, or negative. The condition codes negative and zero are assigned with each non-conditional arithmetic instruction.

Additional functionality such as right shifting, paging, and IO is intended to be mapped to memory locations. This way the basic instruction set remains simple while not prohibiting the design's capabilities.

### Design ###
The initial design of the instruction set can be seen below:
![Initial Design](https://www.lucidchart.com/publicSegments/view/5270ba48-6728-497c-b3ad-632a0a009e11/image.png)


