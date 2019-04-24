# Computer-Systems-Labs-by-CMU

There is a total 6 of them

Data Lab I
This assignment will introduce you to bitwise operations in C, such as bitwise AND (&), OR (|), NOT (~) and right/left shift (>> / <<). The goal is to become familiar with the bit-level representation of integers and with the corner cases of their operations (e.g., two’s complement encoding, signed/unsigned overflow).

Data Lab II
This assignment continues on bitwise operations: in addition to two’s complement integers, it requires the manipulation of IEEE 754 floating point variables (float and double) at the bit level.

Bomb Lab
This assignment gives you a binary program containing “bombs” which trigger a ping to our server (and make you lose points). Your goal is to set breakpoints and step through the binary code using gdb to figure out the program inputs that avoid bombs.

Attack Lab
This assignment asks you to run buffer overflow attacks using two strategies: (1) loading your binary code on the stack and starting its execution by overwriting the return address, or (2) a return-oriented attack, where return addresses are used to jump to one or more gadgets.

Cache Lab
This lab will help you understand the impact that cache memories can have on the performance of your C programs. In this lab, you will write a small C program (about 200-300 lines) that simulates the behavior of a cache memory.

Allocation Lab
In this lab you will be writing a dynamic storage allocator for C programs, i.e., your own version of the malloc, free and realloc routines. You are encouraged to explore the design space creatively and implement an allocator that is correct, efficient and fast.

