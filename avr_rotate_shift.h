
/*
 * Implementation of rotate shift left (or right) by several bit positions on AVR
 * The first number is shift bit positions, and the second number is the size(in bits) of a block.
 * For example, rot_left_1_16 means a 16-bit block is rotated shift left  by 1 bit position.
 * 		rot_right_3_32 means a 32-bit block is rotated shift right  by 3 bit positions.
 * 
 * Author: LuoPeng
 * Time:   2015.10.30
 */

/*
 * For 16-bit block.
 * s0, s1:	8-bit registers. s1 is the higher byte, and s0 is the lower byte. 
 * zero:	register whose value is 0.
 * t0, t1:	Temp registers
 */
#define CONST_0F 0x0f
#define CONST_F0 0xf0
#define ZERO 0
#define SEVEN 7
/* ------------------------------------ */
/* 	Instrcutions	Cycles		*/
/* 	3		3		*/
#define rot_left_1_16(s0, s1, zero)	\
	lsl s0			\n\t	\
	rsl s1			\n\t	\
	adc s0, zero

/* 	6		6		*/
#define rot_left_2_16(s0, s1, zero)	\
	rot_left_1_16(s0, s1, zero)	\
	rot_left_1_16(s0, s1, zero)

/* 	9		9		*/
#define rot_left_3_16(s0, s1, zero)	\
	rot_left_1_16(s0, s1, zero)	\
	rot_left_1_16(s0, s1, zero)	\
	rot_left_1_16(s0, s1, zero)

/* 	7		7		*/
#define rot_left_4_16(s0, s1, t0, t1)	\
	swap s0			\n\t	\
	swap s1			\n\t	\
	movw t0, s0		\n\t	\
	eor  t1, t0		\n\t	\
	andi t1, CONST_0F	\n\t	\
	eor  s0, t1		\n\t	\
	eor  s1, t1		\n\t

/* 	10		10		*/
#define rot_left_5_16(s0, s1, t0, t1, zero)	\
	rot_left_4_16(s0, s1, t0, t1)		\
	rot_left_1_16(s0, s1, zero)

/* 	3		3		*/
#define rot_left_8_16(s0, s1, t0)	\
	mov t0, s0		\n\t	\
	mov s0, s1		\n\t	\
	mov s1, t0		\n\t

/* 	4		4		*/
#define rot_right_1_16(s0, s1)		\
	lsr s1			\n\t	\
	bst s0, ZERO		\n\t	\
	ror s0			\n\t	\
	bld s1, SEVEN

/* 	11		11		*/
#define rot_left_6_16(s0, s1, t0)	\
	rot_left_8_16(s0, s1, t0)	\
	rot_right_1_16(s0, s1)		\
	rot_right_1_16(s0, s1)

/* 	7		7		*/
#define rot_left_7_16(s0, s1, t0)	\
	rot_left_8_16(s0, s1, t0)	\
	rot_right_1_16(s0, s1)

/* 	8		8		*/
#define rot_right_2_16(s0, s1)		\
	rot_right_1_16(s0, s1)		\
	rot_right_1_16(s0, s1)

/* 	10		10		*/
#define rot_right_3_16(s0, s1, t0, t1, zero)	\
	rot_right_4_16(s0, s1, t0, t1)		\
	rot_left_1_16(s0, s1, zero)

/* 	7		7		*/
#define rot_right_4_16(s0, s1, t0, t1)	\
	swap s0			\n\t	\
	swap s1			\n\t	\
	movw t0, s0		\n\t	\
	eor  t1, t0		\n\t	\
	andi t1, CONST_F0	\n\t	\
	eor  s0, t1		\n\t	\
	eor  s1, t1		\n\t

/* 	11		11		*/
#define rot_right_5_16(s0, s1, t0, t1)	\
	rot_right_4_16(s0, s1, t0, t1)	\
	rot_right_1_16(s0, s1)

/* 	9		9		*/
#define rot_right_6_16(s0, s1, t0, zero)\
	rot_left_8_16(s0, s1, t0)	\
	rot_left_1_16(s0, s1, zero)	\
	rot_left_1_16(s0, s1, zero)

/* 	6		6		*/
#define rot_right_7_16(s0, s1, t0, zero)\
	rot_right_8_16(s0, s1, t0)	\
	rot_left_1_16(s0, s1, zero)	\

/* 	3		3		*/
#define rot_right_8_16(s0, s1, t0)	\
	rot_left_8_16(s0, s1, t0)
/* ------------------------------------ */

/*
 * For 32-bit block.
 * s0, s1, s2, s3:	8-bit registers. s3 is the most significant byte, and s0 is the least significant byte. 
 * zero:		register whose value is 0.
 * t0, t1, t2, t3:	Temp registers
 */
/* ------------------------------------ */
/* 	Instrcutions	Cycles		*/
/* 	5		5		*/
#define rot_left_1_32(s0, s1, s2, s3, zero)	\
 	lsl s0				\n\t	\
 	rol s1				\n\t 	\
	ror s2				\n\t	\
	ror s3 				\n\t	\
	adc s0, zero			\n\t

/* 	10		10		*/
#define rot_left_2_32(s0, s1, s2, s3, zero)	\
	rot_left_1_32(s0, s1, s2, s3, zero)	\
	rot_left_1_32(s0, s1, s2, s3, zero)

/* 	15		15		*/
#define rot_left_3_32(s0, s1, s2, s3, zero)	\
	rot_left_1_32(s0, s1, s2, s3, zero)	\
	rot_left_1_32(s0, s1, s2, s3, zero)	\
	rot_left_1_32(s0, s1, s2, s3, zero)

/* 	15		15		*/
#define rot_left_4_32

#define rot_left_5_32

#define rot_left_6_32

#define rot_left_7_32

/* 	5		5		*/
#define rot_left_8_32(s0, s1, s2, s3, t0)	\
	mov t0, s3			\n\t	\
	mov s3, s2			\n\t	\
	mov s2, s1			\n\t	\
	mov s1, s0			\n\t	\
	mov s0, t0			\n\t

#define rot_left_9_32

#define rot_left_10_32

#define rot_left_11_32

#define rot_left_12_32

#define rot_left_13_32

#define rot_left_14_32

#define rot_left_15_32

/* 	6		6		*/
#define rot_left_16_32(s0, s1, s2, s3, t0)	\
	mov t0, s3			\n\t	\
	mov s3, s1			\n\t	\
	mov s1, s3			\n\t	\
	mov t0, s2			\n\t	\
	mov s2, s0			\n\t	\
	mov s0, t0			\n\t

#define rot_right_1_32

#define rot_right_2_32

#define rot_right_3_32

#define rot_right_4_32

#define rot_right_5_32

#define rot_right_6_32

#define rot_right_7_32

/* 	5		5		*/
#define rot_right_8_32(s0, s1, s2, s3, t0)	\
	mov t0, s0			\n\t	\
	mov s0, s1			\n\t	\
	mov s1, s2			\n\t	\
	mov s2, s3			\n\t	\
	mov s3, t0			\n\t

#define rot_right_9_32

#define rot_right_10_32

#define rot_right_11_32

#define rot_right_12_32

#define rot_right_13_32

#define rot_right_14_32

#define rot_right_15_32

/* 	6		6		*/
#define rot_right_16_32(s0, s1, s2, s3, t0)	\
	rot_left_16_32(s0, s1, s2, s3, t0)
