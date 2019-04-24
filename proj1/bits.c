/* 
 * CS:APP Data Lab 
 * 
 * <Minxuan Song 7618212030>
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.


EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implement floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants. You can use any arithmetic,
logical, or comparison operations on int or unsigned data.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
/* Copyright (C) 1991-2016 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */
/* This header is separate from features.h so that the compiler can
   include it implicitly at the start of every compilation.  It must
   not itself include <features.h> or any other header that includes
   <features.h> because the implicit include comes before any feature
   test macros that may be defined in a source file before it first
   explicitly includes a system header.  GCC knows the name of this
   header in order to preinclude it.  */
/* glibc's intent is to support the IEC 559 math functionality, real
   and complex.  If the GCC (4.9 and later) predefined macros
   specifying compiler intent are available, use them to determine
   whether the overall intent is to support these features; otherwise,
   presume an older compiler has intent to support these features and
   define these macros by default.  */
/* wchar_t uses Unicode 8.0.0.  Version 8.0 of the Unicode Standard is
   synchronized with ISO/IEC 10646:2014, plus Amendment 1 (published
   2015-05-15).  */
/* We do not support C11 <threads.h>.  */
/* 
 * bitOr - x|y using only ~ and & 
 *   Example: bitOr(6, 5) = 7
 *   Legal ops: ~ &
 *   Max ops: 8
 *   Rating: 1
 */
int bitOr(int x, int y) {
  //flip the bits of x, flips the bits of y
  //and them, and then get the complement of them,
  //here we obtain  the x|y
  //basically deleting every bit that's not in the x nor y, and the rest is there
  return ~((~x)&(~y));
}
/* 
 * oddBits - return word with all odd-numbered bits set to 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 2
 */
int oddBits(void) {
  //0xaa is the largest bit allowed in rules that yield odds
  // its 01010101. and we get 010101010101
  // and then we get 010101010101 x 2
  // pretty straight forward.
  return ((0xaa | 0xaa<<8)<<16)|(0xaa | 0xaa<<8);
}
/* 
 * leastBitPos - return a mask that marks the position of the
 *               least significant 1 bit. If x == 0, return 0
 *   Example: leastBitPos(96) = 0x20
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2 
 */
int leastBitPos(int x) {
  // this is done by getting the complement of x,
  // and we know that the complement of them each will never & to any value
  // then, we add a one, shifting the value left
  //say, we have 10000, and complement is 01111, and add 1, we have 10000,
  //& this, we get the mask which has the place marked for the least significant bit.
  // is it the same effect if we don't add 1 but shift it leftwards tho?
  // no. as is verified by me, if all the bits are non-zero and the last bit is the
  // least significant bit, we get its complement as 0.
  //however, what if we return 0x01 if we get 0? no. we neglect the negative number case
  return x&(~x+1);
}
/* 
 * isPositive - return 1 if x > 0, return 0 otherwise 
 *   Example: isPositive(-1) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 2
 */
int isPositive(int x) {
  // first, we shift the bits to the right, leaving only the
  // first bit which shows the sign available
  // then, we check if it's zero (because zero is intepreted as positive here)
  // then, we compare this to a known positive number, i choose 1 here
  // then, return.
  return !(x >> 31) & !!x;
}
/* 
 * isLess - if x < y  then return 1, else return 0 
 *   Example: isLess(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLess(int x, int y) {
  // remember to delete variables
  //if not same sign, which is the left side
  //we don't compare
  // if same sign, we compare
  // there's a table to draw all of this, and the | sign is the if/else
  //r: residue of x-y
  int r = x + (~y+1);int rsign = (r>>31) & 1;int fx = (x>>31) & 1;int fy = (y>>31) & 1;
  // fxfy is the sign for everything
  return ((fx) ^ (fy) & (fx) | (!(fx^fy))&rsign);
  //one line implementation of what's above
  // return ((( ((x>>31) & 1) ^ ((y>>31) & 1)  ) & ((x>>31) & 1) ) | ((!( ((x>>31) & 1) ^ ((y>>31) & 1) )) & (( (x + (~y+1)) >>31) & 1) ));
}
/* 
 * subtractionOK - Determine if can compute x-y without overflow
 *   Example: subtractionOK(0x80000000,0x80000000) = 1,
 *            subtractionOK(0x80000000,0x70000000) = 0, 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int subtractionOK(int x, int y) {
  // nope, if n+n = p, overflow, if p+p = n, overflow
  //so, i just need to check sign
  // remember, !! if non zero = 1
  // it's the same logic in less than/
  int r = x + (~y+1);
  int fx = (x>>31) & 1;
  int fy = (y>>31) & 1;
  int rsign = (r>>31) & 1;
  return ((!(fx ^ fy) ) | (((fx ^ fy)) & (!(fx^rsign))));
  //5 line implementation of what's below (the one below doesn't meet the max ops requirement)
  // return ((!(((x>>31) & 1) ^ ((y>>31) & 1) ) ) | (((((x>>31) & 1) ^ ((y>>31) & 1) )) & (!(((x>>31) & 1)^ (( (x + (~y+1)) >>31) & 1) ))));
}
/*
 * ezThreeFourths - multiplies by 3/4 rounding toward 0,
 *   Should exactly duplicate effect of C expression (x*3/4),
 *   including overflow behavior.
 *   Examples: ezThreeFourths(11) = 8
 *             ezThreeFourths(-9) = -6
 *             ezThreeFourths(1073741824) = -268435456 (overflow)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 3
 */
int ezThreeFourths(int x) {
  //for this problem, we first get x multiplied by 3
  //then, we get the sign of this number
  // then, we create a mask that's only the first 2 digit of the 32bit turned to 1
  //because we are shifting everything rightwards by 2, it's division by 4
  //now, the vital part, if signx3 == 0, we get 0 from this mask therefore x3 goes 2 bits rightwards
  //if signx3 != 0, then we have a whole 32 bits of 1, and then the mask produces 3.
  //Adding this 3 precisely add to the first 2 empty digits waiting to be filled as 1 of the binary negative
  // in two's complement.
   // int x3 = x+x+x;
   // int signx3 = x3>>31;
   // int divby4m = 3;
   // return ((x3 + (divby4m & signx3)) >> 2);
  //one line version of what's above
  return (((x+x+x)+(3&((x+x+x)>>31)))>>2);
}
