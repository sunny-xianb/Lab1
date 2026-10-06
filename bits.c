/* 
 * CS:APP Data Lab 
 * 
 * <Please put your name and userid here>
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
  4. Interprets integer expressions using the Data Lab 32-bit bit-vector
     model: results outside the signed range retain their low 32 bits.


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
#include "bits.h"

// P1
/* 
 * signMask - return a mask with only the most significant bit set (0x80000000)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 2
 *   Rating: 1
 */
int signMask(void) {
  return 1<<31;
}

// P2
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1, bitXor(7, 7) = 0
 *   Legal ops: ~ &
 *   Max ops: 8
 *   Rating: 2
 */
int bitXor(int x, int y) {
	return ~(x&y)&~(~x&~y);
}

// P3
/*
 * negativePart - return -x if x < 0, otherwise return 0
 *   Examples: negativePart(-10) = 10, negativePart(5) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 3
 */
int negativePart(int x){
  int mask=x>>31;
  return (mask & (~x)) + (mask & 1);
}


// P4
/*
 * copyByteWithin - copy byte src of x to byte dst, leaving all other bytes unchanged
 *   Bytes are numbered from 0 (least significant) to 3 (most significant).
 *   You can assume 0 <= src <= 3 and 0 <= dst <= 3.
 *   Example: copyByteWithin(0x11223344, 0, 2) = 0x11443344
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4
 */
int copyByteWithin(int x, int src, int dst) {
  int srcShift = src<<3;
  int c = (x>>srcShift&0xFF);
  int dstShift = dst<<3;
  int move = c<<dstShift;
  int mask = ~(0xFF<<dstShift);
  return (x&mask)|move;
}

// P5
/* 
 * logicalShift - shift x to the right by n bits, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int logicalShift(int x, int n) {
  int a = x>>n;
  int mask = ~((1<<31)>>n<<1);
  return a&mask;
}

// P6
/*
 * swapNibblePairs - swap the low and high 4 bits within each byte of x
 *   Examples: swapNibblePairs(0xAB) = 0xBA
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 18
 *   Rating: 4
 */
int swapNibblePairs(int x) {
  int mask = 0x0F;
  mask = mask | (mask << 8);
  mask = mask | (mask << 16);
  int high = (x>>4)&mask;
  int low = (x&mask)<<4;
  return high|low;
}

// P7
/*
 * secondLowestZeroBit - return a mask that marks the position of the second least significant 0 bit
 *   Examples: secondLowestZeroBit(0xFFFFFFFA) = 0x4, secondLowestZeroBit(0x7FFFFFFF) = 0
 *             secondLowestZeroBit(-1) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 4
 */
int secondLowestZeroBit(int x) {
  int z = ~x;          
  int lsb = z & (~z + 1); 
  z = z ^ lsb;         
  return z & (~z + 1);  
}

// P8
/*
 * oddParity - return the odd parity bit of x, that is,
 *      when the number of 1s in the binary representation of x is even, then the return 1, otherwise return 0.
 *   Examples: oddParity(5) = 1, oddParity(7) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 56
 *   Rating: 5
 */
int oddParity(int x) {
  x^=x>>16;
  x^=x>>8;
  x^=x>>4;
  x^=x>>2;
  x^=x>>1;
  return !(x&1);
}

// P9
/* 
 * rotateRightBits - rotate x to right by n bits
 *   you can assume n >= 0
 *   Examples: rotateRightBits(0x12345678, 8) = 0x78123456
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 5
 */
int rotateRightBits(int x, int n) {
  int rot = n & 31;
  int negRot = ~rot + 1;
  int leftPart = x << (32 + negRot);
  int mask = ~((1 << 31) >> rot << 1);
  int rightPart = (x >> rot) & mask;
  return leftPart | rightPart;
}

// P10
/*
 * roundEvenPow2 - round nonnegative x to the nearest multiple of 2^n.
 *   If x is exactly halfway between two multiples, choose the multiple whose
 *   quotient by 2^n is even.
 *   You can assume 0 <= x <= 0x3fffffff and 1 <= n <= 16.
 *   Examples: roundEvenPow2(10, 2) = 8, roundEvenPow2(14, 2) = 16
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 5
 */
int roundEvenPow2(int x, int n) {
  int k = n + ~0;
  int mask = (1 << n) + ~0;
  int low = x & mask;
  int half = 1 << k;
  int high = low >> k;
  int neq = !!(low ^ half);
  int odd = (x >> n) & 1;
  int up = high & (neq | odd);

  return (x & ~mask) + (up << n);
}

// P11
/* 
 * midpointTowardFirst - return the exact mathematical midpoint (x+y)/2
 *   without overflow. If the exact midpoint lies halfway between two
 *   integers, choose the adjacent integer that is closer to the first
 *   argument x.
 *   Examples: midpointTowardFirst(4, 7) = 5,
 *             midpointTowardFirst(7, 4) = 6
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 32
 *   Rating: 5
 */
int midpointTowardFirst(int x, int y) {
  int sa = x & y;
  int df = x ^ y;
  int md = sa + (df >> 1);

  int sx = (x >> 31) & 1;
  int sy = (y >> 31) & 1;
  int ds = sx ^ sy;

  int gt_d = ds & (!sx);

  int ny = ~y + 1;
  int sub = x + ny;
  int ss = (sub >> 31) & 1;
  int gt_s = (!ds) & (!ss);

  int gt = gt_d | gt_s;
  int half = df & 1;
  int inc = half & gt;

  return md + inc;
}


// P12
/* 
 * isBetweenEitherOrder - return 1 when x lies in the inclusive interval whose
 *   endpoints are a and b. The endpoints may be given in either order.
 *   Example: isBetweenEitherOrder(5, 8, 3) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 48
 *   Rating: 7
 */
int isBetweenEitherOrder(int x, int a, int b) {
  int sx = x >> 31;
  int sa = a >> 31;
  int sb = b >> 31;
  int xa = x + ~a + 1;
  int xb = x + ~b + 1;
  int ax = a + ~x + 1;
  int bx = b + ~x + 1;

  int la = (sx & !sa) | (((!(sx ^ sa)) & (xa >> 31)));
  int lb = (sx & !sb) | (((!(sx ^ sb)) & (xb >> 31)));
  int lax = (sa & !sx) | (((!(sa ^ sx)) & (ax >> 31)));
  int lbx = (sb & !sx) | (((!(sb ^ sx)) & (bx >> 31)));

  return !((la & lb) | (lax & lbx));
}

// P13
/* 
 * mul5Sat - return x*5, and if x*5 overflow, change the result to 
 * INT_MAX(0x7fffffff) or INT_MIN(0x80000000) correspondingly
 *   Examples: mul5Sat(1) = 0x5, mul5Sat(0x40000000) = 0x7fffffff
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 30
 *   Rating: 7
 */
int mul5Sat(int x) {
  int x4 = x<<2;
  int over = !!((x4>>2)^x);

  int res= x4+x;

  over = over |(((res^x)>>31)&1);
  
  int mask = ~over+1;
  int INF = (1<<31)^(~(x>>31));

  return ((~mask)&res)|(mask&INF);
}
// P14
/* 
 * classifyAdd3 - classify the exact mathematical sum x+y+z.
 *   Return 1 if the sum is greater than INT_MAX, -1 if it is less than
 *   INT_MIN, and 0 otherwise. You may not use a wider integer type.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 52
 *   Rating: 7
 */
int classifyAdd3(int x, int y, int z) {
  int sum1 = x + y;     
  int sum2 = sum1 + z;

  int c1 = ((((~x )& (~y) & sum1) >> 31) & 1)  + ((x & y & (~sum1)) >> 31);
  int c2 = ((((~sum1) & (~z) & sum2) >> 31) & 1) + ((sum1 & z & (~sum2)) >> 31);
  
  int c = c1 + c2;
  return (c >> 31)| (!!c);
}

// P15
/*
 * floatScaleThreeHalves - Return bit-level equivalent of expression f*3/2 for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   Use round-to-nearest-even. Preserve the sign of both +0 and -0.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 60
 *   Rating: 7
 */
unsigned floatScaleThreeHalves(unsigned uf) {
  unsigned sign = uf & 0x80000000;
  unsigned exp = (uf >> 23) & 0xff;
  unsigned frac = uf & 0x7fffff;
  if (exp == 0xff) return uf; 
  if (exp == 0) {
      unsigned res = frac*3;
    int round = ((res & 3) == 3);

    res = (res >> 1) + round;
    
    if (res >= 0x800000) return sign | (1 << 23) | (res & 0x7fffff);
    return sign | res;
  }

  unsigned res = (frac | 0x800000) * 3;
  if (res >= 0x2000000)
  {
    exp = exp + 1;
    int round = ((res & 3) > 2) || (((res & 3) == 2) && ((res >> 2) & 1));
    res = (res>>2)+round;
  }
  else
  {
    int round = ((res & 3)==3);
    res = (res>>1)+round;
  }
  if (res >= 0x1000000) {
    res = res>>1;
    exp = exp+1;
  }
  if (exp >= 0xff) return sign | 0x7f800000;
  return sign | (exp << 23) | (res & 0x7fffff);
}

// P16
/* 
 * floatRoundEven - round the floating-point value represented by uf to the
 *   nearest integer, with halfway cases rounded to the even integer. Return
 *   the bit-level representation of that integer as a single-precision float.
 *   If rounding produces zero, preserve the input sign; thus a negative
 *   value that rounds to zero returns -0. When uf is NaN or infinity,
 *   return uf unchanged.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 65
 *   Rating: 10
 */
unsigned floatRoundEven(unsigned uf) {
  unsigned sign = uf&0x80000000;
  unsigned exp=(uf>>23)&0xff;
  int e =exp-127;
  if(exp == 0xff)return uf;
  if (e<-1)return sign;
  if (e==-1) {
    if (uf& 0x7fffff) return sign|0x3f800000;
    return sign;
  }
  if(e>=23)return uf;
  int shift = 23-e;
  int mask = (1 << shift) - 1;
  int half = 1 << (shift - 1);
  int low = uf & mask;
  int round = (low > half) || ((low == half) && ((uf >> shift) & 1));
  return (uf & ~mask) + (round << shift);
}

// P17
/*
 * float_i2f - Return bit-level equivalent of expression (float) x.
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 40
 *   Rating: 10
 */
unsigned float_i2f(int x) {
  if (x == 0)
        return 0;
    if (x == 0x80000000)
        return 0xcf000000;

    unsigned sign = 0;
    if (x < 0) {
        sign = 0x80000000;
        x = -x;
    }

    int exp = 30;
    while (!((x >> exp) & 1))
        --exp;

    if (exp <= 23) {
        return sign | ((exp + 127) << 23) | ((x << (23 - exp)) & 0x7fffff);
    }

    int shift = exp - 23;
    int mask = (1 << shift) - 1;
    int half = 1 << (shift - 1);
    int low = x & mask;

    int round = (low > half) || ((low == half) && ((x >> shift) & 1));
    x = (x >> shift) + round;

    if (x >> 24) {
        x = x >> 1;
        exp = exp + 1;
    }

    return sign | ((exp + 127) << 23) | (x & 0x7fffff);
}



// P18
/*
 * bitCount - return count of number of 1's in the binary representation of x
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 10
 */
int bitCount(int x) {
  int mask_1 = 85+(85<<8);
  int mask_2 = 51+(51<<8);
  int mask_4 = 15+(15<<8);
  mask_1 = mask_1+(mask_1<<16);
  mask_2 = mask_2+(mask_2<<16);
  mask_4 = mask_4+(mask_4<<16);

  x=(x&mask_1)+((x>>1)&mask_1);
  x=(x&mask_2)+((x>>2)&mask_2);
  x=(x+(x>>4))&mask_4;
  x=x+(x>>8);
  x=x+(x>>16);
  return x&63;
}

// P19
/*
 * bitReverse - Reverse bits in an 32-bit integer
 *   Examples: bitReverse(0x80000004) = 0x20000001
 *             bitReverse(0x7FFFFFFF) = 0xFFFFFFFE
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 34
 *   Rating: 10
 */
int bitReverse(int x)
{
  int mask_16 = (1<<16) + (~1+1);
  x = (((x >> 16) & mask_16)) | (((x & mask_16) << 16));

  int mask_8 = 255 + (255<<16);
  x = (((x >> 8) & mask_8)) | (((x & mask_8) << 8));

  int mask_4 = 15 + (15<<8) + (15<<16) + (15<<24);
  x = (((x >> 4) & mask_4)) | (((x & mask_4) << 4));

  int mask_2 = 3 + (3<<4) + (3<<8) + (3<<12) + (3<<16) + (3<<20) + (3<<24) + (3<<28);
  x = (((x >> 2) & mask_2)) | (((x & mask_2) << 2));

  int mask_1 = 1 + (1<<2) + (1<<4) + (1<<6) + (1<<8) + (1<<10) + (1<<12) + (1<<14)
    + (1<<16) + (1<<18) + (1<<20) + (1<<22) + (1<<24) + (1<<26) + (1<<28) + (1<<30);
  x = (((x >> 1) & mask_1)) | (((x & mask_1) << 1));

  return x;
}
