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
//1
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */


//异或:同位不同则为1，考虑&和~的特性
//&:两数均为1可以得到1，其他情况为0，~可以将数取反:可以让原来为0的位置变成1
//因此可以先求与得到两数均为1的位置(x & y)，取反后可将这些位置置零~(x & y)，此时高位均为1
//然后可以将两数均为0时的位置置零~(~x & ~y)，此时高位均为0
//两者相与即可得到最终结果
int bitXor(int x, int y) {
  return ~(x & y) & ~(~x & ~y);
}


/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */

//即需要返回0b1000...1000，0x80000000
int tmin(void) {

  return 1 << 31;

}

//2
/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */

//如果是0x7fffffff返回1，否则返回0
//只有两种情况分别对应0和1，所以想到!
//~Tmax可以得到Tmin，而两个Tmin相加就可以得到0，取非得到1
//但是这种方法在-1那里也成立，需要排除-1的情况，考虑~-1后得到0，所以再!后得到一个会对最终结果产生影响的1
//(其他值则不会)，因为取反后不为0
int isTmax(int x) {
  int temp = ~x;
  
  return !(temp + temp + !temp); 
}

/* 
 *
 * allOddBits - return 1 if all odd-numbered bits in word set to 1
 *   where bits are numbered from 0 (least significant) to 31 (most significant)
 *   Examples allOddBits(0xFFFFFFFD) = 0, allOddBits(0xAAAAAAAA) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */

//奇数位均为1，说明x & 0xaaaaaaaa == 0xaaaaaaaa
//所以需要先生成一个0xaaaaaaaa的掩码
//如果满足条件相与后仍为这个值，再与本身取异或得到0
int allOddBits(int x) {
  int t1 = 0xaa;  		//8位  0b1010 1010
  int t2 = t1 | t1 << 8;	//16位 0xaa aa
  int t3 = t2 | t2 << 16;	//32位 0xaaaa aaaa
  
  return !((x & t3) ^ t3);
}


/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */

//各位取反，末尾加一
int negate(int x) {
  return ~x + 1;
}

//3
/* 
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0' to '9')
 *   Example: isAsciiDigit(0x35) = 1.
 *            isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */

//0x30~0x39可以划分成两种情况  后8位从0011 0000 ~ 0011 1001
//1.后8位为0011 0xxx	2.后8位为0011 100x
int isAsciiDigit(int x) {
  int mask1 = ~7;		//掩码1: 11... 1111 1000 (将最后三位置零)
  int mask2 = ~1;		//掩码2: 11... 1111 1110 (将最后一位置零)
  
  int t1 = x & mask1;
  int t2 = x & mask2;

  return !(t1 + ~0x30 + 1) | !(t2 + ~0x38 + 1);
}


/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */

//如果x != 0，返回y，否则返回z
int conditional(int x, int y, int z) {
  int temp = ~(!x) + 1 ;	//如果x == 0,temp为-1(全1),如果x != 0,temp为0

  return (~temp & y) | (temp & z);
}


/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */

//先计算出sum = x + (-y)的值
//创建一个变量isEqual记录x与y符号位是否相同
//如果符号位不相同，此时只有x为负(符号位为1)返回1
//如果符号位相同，可能x == y或者 x < y(分别对应结果sum == 0和sum 符号位为1)
int isLessOrEqual(int x, int y) {
  //计算结果和符号位
  int z = ~y + 1;		//-y
  int sum = x + z;		//计算结果
  int sx = x >> 31;		//x符号位
  int sy = y >> 31;		//y符号位  
  int isEqual = (sx ^ sy) & 1;	//若符号位相同是0,否则是1
  
  int part1 = isEqual & sx;     //x、y符号位不同，只有当x为负数时成立
  int part2 = !isEqual & (!sum | sum >> 31);    //x、y符号位相同，可能两数相等或者一大一小(结果为0或结果符号位为1)

  return part1 | part2;
}


//4
/* 
 * logicalNeg - implement the ! operator, using all of 
 *              the legal operators except !
 *   Examples: logicalNeg(3) = 0, logicalNeg(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */

//如果值是0返回0，其他情况返回1
//注意到绝大多数数字取负后符号位与本身不同，所以两数符号位取或后得到1
//对于0x80000000也一样(虽然它取负后仍为0x80000000)
int logicalNeg(int x) {
  int negX = ~x + 1;

  return ((x | negX) >> 31) + 1;
}

/* howManyBits - return the minimum number of bits required to represent x in
 *             two's complement
 *  Examples: howManyBits(12) = 5
 *            howManyBits(298) = 10
 *            howManyBits(-5) = 4
 *            howManyBits(0)  = 1
 *            howManyBits(-1) = 1
 *            howManyBits(0x80000000) = 32
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 90
 *  Rating: 4
 */
//如果x是正数那么需要找到x中最高位上的1，如果x是负数那么需要找到x中最高位上的0
//最后结果等于这个数加一(加上前面的符号位)
//如果x是负数可将x取反，这样最高位的0就变成了最高位的1
//然后按照类似二分查找的方法，不断缩小范围
int howManyBits(int x) {
  int b16, b8, b4, b2, b1, b0;
  int sign = x >> 31;             //获得符号位
  x = (~sign & x) | (sign & ~x);  //正数不变，负数取反

  b16 = !!(x >> 16) << 4;         //检查前16位中是否有1
  x >>= b16;                       //如果高16位中有，那么将x右移缩小范围
  //如果上一轮已经确定1在前16位，那么此时则检查这16位中的前8位，否则转而检测原数的前24中是否有1
  b8 = !!(x >> 8) << 3;          
  x >>= b8;                        //如果存在则缩小范围，否则检测后面的位
  b4 = !!(x >> 4) << 2;           //检查前4位           
  x >>= b4;
  b2 = !!(x >> 2) << 1;
  x >>= b2;
  b1 = !!(x >> 1);                
  x >>= b1;
  b0 = x;
  //此时b16、b8、b4、b2、b1的值分别表示检查区间前半部分是否存在1(如果有则需要添加相应的位数)
  return b16 + b8 + b4 + b2 + b1 + b0 + 1;
}

//float
/* 
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */

//E = exp - 127
//对于大多数情况(不溢出):乘二相当于小数点向右移动一位:指数直接加一(符号位不变)
//NaN:exp == 255，尾数非零
//几个特殊情况，0返回0，无穷大返回无穷大
unsigned floatScale2(unsigned uf) {
  int exp = (uf >> 23) & 0xff;    //取出指数位
  int left = uf & 0x7ffff;        //取出尾数部分(小数点后)
  int carry = 0;

  //如果是无穷大或NAN
  if (exp == 255)
    return uf;

  if (exp == 0)
  {
    if (left == 0)  //0
      return uf;
    //非规格化数将尾数左移一位
    if (uf & 0x400000)    //如果首位是1，需要进位
      carry = 0x800000;
    //前9位加上尾数部分
    return ((uf & 0xff800000) + carry) | ((uf << 1) & 0x7fffff);     
  }

  //其他情况指数位加一即可
  return uf + 0x800000;
}
/* 
 * floatFloat2Int - Return bit-level equivalent of expression (int) f
 *   for floating point argument f.
 *   Argument is passed as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point value.
 *   Anything out of range (including NaN and infinity) should return
 *   0x80000000u.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
int floatFloat2Int(unsigned uf) {
  //E = exp - 127
  int exp = (uf >> 23) & 0xff;    //提取指数位
  int left = uf & 0x7fffff;       //提取尾数位
  // int result = 1;                 //如果指数位是0(非规格化数则略去这个1)
  int sign = uf & 0x80000000;     //符号位
  int e = exp - 127;              //实际指数
  int result;

  //如果整型无法表示(包含NaN或者无穷大)直接返回特定值
  if (exp == 255 || e > 30)
    return 0x80000000;
  //非规格化数或者指数小于0的数再截断小数后会变成0
  if (exp < 127)
    return 0;

  result = (1 << e) | (left >> (23 - e));
  if (sign)
    result = -result;
  
  return result;
}
/* 
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 * 
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. Also if, while 
 *   Max ops: 30 
 *   Rating: 4
 */
//浮点数正数上界和下界：上界1.1111...1111 * 2^127，下界 0.000....0001 * 2^-126(2^-149)
//若x > 127，上溢出; 若x < -149，下溢出
//x >= 0：规格化数，x < 0：非规格化数
//规格化数均可写成 1.0 * 2 ^ x: 说明如果是规格化数，阶码不为0，尾数为0
//非规格化数可写成 0.f * 2 ^ -126: 阶码全0，尾数不为0 :非规格化数范围[2^-149-2^-126)
unsigned floatPower2(int x) {

    //是否上溢出
    if (x > 127)
      return 0x7f800000;
    //是否下溢出
    if (x < -149)
      return 0;
    //是否是非规格化数:阶码全0
    if (x < -126)
      return 0x00800000 >> (-126 - x);
    //是规格化数:尾数全0
    return (127 + x) << 23;
}
