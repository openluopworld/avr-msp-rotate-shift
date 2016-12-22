# Instruction Set
* C(Carry); V(overflow); N(negative); and Z(zero)
* [MSP430 Quick Reference(*)], [More Details of MSP430]
* [AVR Instruction Set]
* ARM Instruction Set [1], [2]
* In MSP and ARM, the higher bytes are loaded to the higher address of register. Therefore, the order of test values are opposite to the paper.

## MSP430

### MSP430 Introduction
Brief Introduction: 16 16-bit register. Four of the registers are dedicated to program counter(r0 or pc), stack point(r1 or sp), status register(r2 or sr/cg1) and constant generator(r3 or cg2), while the remaining 12 registers(r4-r15) are general-purpose registers. There are 52 instructions in total.

* Instructions in MSP are different with other microcontrollers.
  + <b>The first register is the source, the second is the destination</b>.
  + For example, <b>mov r5, r4</b> means moving r5 to r4.

* <b>[bit rs, rd]</b> : rs & rd; Set status only, the destination is not written.

* Logical instructions set C to the opposite of Z (C is set if the result is NOT zero), and clear V to 0.
  + For example: the following instructions rotate shift right (r9:r8) by 1 bit.
```C
bit #1, r8;
rrc r9;
rrc r8;
```

* <b>A byte instruction with a register destination clears the higher 8 bits of the register to 0</b>.
  + For example, <b>[mov.b r6, r12]</b> means moving the lower 8 bits of r6 to r12, and the higher 8 bits of r12 is set to 0.

* <b>[mov(.b) @rs+, rd]</b> : Indirect autoincrement. The operand is in memory at the address held in rs, then the register rs is incremented by 1(operation in byte) or 2(operation in word).
  + For example: load the plain text from RAM(r15 stores the start address) to register[r7,r6,r5,r4]
```C
mov    @r15+,    r4;
mov    @r15+,    r5;
mov    @r15+,    r6;
mov    @r15+,    r7;
```

* [Calling Convention and ABI Changes in MSP GCC]
  + [r15-r12]: In MSPGCC, registers are passed starting with R15 and descending to R12. For example, if two integers are passed, the first is passed in R15 and the second is passed in R14.
  + [r11-r4]: r11-r4 must be pushed if used.

* The stack pointer is always even. So <b>pop</b> and <b>pop.b</b> instructions will all increase SP by 2. And <b>push</b> and <b>push.b</b> instructions will all decrease SP by 2.

### MSP rotate shift
The least number of instructions needed for rotate shift. It means rotating shift <b>right</b> if x is positive, otherwise rotating shift left. The red pointers are the basic operations which can not be implemented by others. For example, <i>rotate shift left by 2 bits</i> can be implemented using <i>rotate shift left by 1 bit</i> twice. But it can not be done in turn. (It is the same for AVR)

### Results for 16-bit block on MSP
![rotate shift for 16-bit block on MSP](./pic/msp_results.png?raw=true)<br>

## AVR

### AVR Introduction
Most of the 133 instructions require a single cycle to execute. The rich instruction set in combimed with the 32 8-bit general purpose registers(r0-r31) with single clock access time. Six of the 32 8-bit registers can be used as three 16-bit indirect register pointers(X, r26-r27; Y, r28-r29; and Z, r30-r31) for addressing the data space.<br>

* Instruction <b>ldi r26, low(key)</b> and <b>ldi r27, high(key)</b> can not be used in assemble c. It should be like this <b>ldi r26, lo8(key)</b> and <b>ldi r27, hi8(key)</b>.

* Despite using <i>#include"constants.h"</i>, some const values, such as KEY_SIZE, NUMBER_OF_ROUNDS and so on, can still not be used directly. Therefore, immediate numbers are used.

* The second operand of <b>adiw</b> is belong to [0, 63].
Therefore, adiw r28, 176 is wrong(operand is out of range). It can be replaced by:
  + adiw r28, 63;
  + adiw r28, 63;
  + adiw r28, 50;

* Implementation problems:
  + 1)AVR: relocation truncated to fit: R_AVR_7_PCREL against 'no symbol'; 2)MSP: '#' is not followed by a macro parameter compilation terminated due to -Wfatal-errors.
  + Reason: In avr_basic_asm_macros.h and msp_basic_asm_macros.h, some const values can not be used in instructions directly.
  + Solution: Something like "#define DFDZero #0xff00" (in msp) and "#define CONST_F0 0xf0"(in avr) is used.<br>

  + AVR: Error: register r24, r26, r28 or r30 required<br>
  + Solution: Change sbiw z, 16 to sbiw r30, 16 of dec_keyxor_flash_ in avr_basic_asm_macros.h. See [AVR-GCC Inline Assembler Cookbook]<br>

  + AVR: decrypt.c:52:(.text.Decrypt+0xae): relocation truncated to fit: R_AVR_7_PCREL against 'no symbol'
  + Reason: <b>brne</b> can NOT be used when the address is beyond [-63, 64]<br>
  + Solution: <b>rjmp</b> is used instead of <b>brne</b><br>

### Results for 16-bit block on AVR
![rotate shift for 16-bit block on AVR](./pic/avr_results.png?raw=true)<br>

### ARM
* <b>mov r4, #0xdbac65e0</b> gives the error message [invalid constant (dbac65e0) after fieup].
The following instructions can implement it:
```C
mov r4, #0xdb
lsl r4, #8
eor r4, r4, #0xac
lsl r4, #8
eor r4, r4, #0x65
lsl r4, #8
eor r4, r4, #0xe0
```

* <b>stmia(stmib), stmdb(stmda), ldmia(ldmib), ldmdb(ldmda)</b>
  + ia ----> increase after
  + db ----> decrease before
  + ib ----> increase before
  + da ----> decrease after


[MSP430 Quick Reference(*)]:<http://www.ece.utep.edu/courses/web3376/Links_files/MSP430%20Quick%20Reference.pdf>
[More Details of MSP430]:<http://mspgcc.sourceforge.net/manual/book1.html>
[AVR Instruction Set]:<http://www.atmel.com/images/atmel-0856-avr-instruction-set-manual.pdf>
[1]:<http://infocenter.arm.com/help/topic/com.arm.doc.qrc0001m/QRC0001_UAL.pdf>
[2]:<http://infocenter.arm.com/help/topic/com.arm.doc.ddi0337h/DDI0337H_cortex_m3_r2p0_trm.pdf>
[bit rs, rd]:<http://mspgcc.sourceforge.net/manual/x223.html>
[mov.b r6, r12]:<http://mspgcc.sourceforge.net/manual/x214.html>
[mov(.b) @rs+, rd]:<http://www.ece.utep.edu/courses/web3376/Links_files/MSP430%20Quick%20Reference.pdf>
[Calling Convention and ABI Changes in MSP GCC]:<http://www.ti.com/lit/an/slaa664/slaa664.pdf>
[AVR-GCC Inline Assembler Cookbook]:<http://www.nongnu.org/avr-libc/user-manual/inline_asm.html>
[invalid constant (dbac65e0) after fieup]:<http://stackoverflow.com/questions/10261300/invalid-constant-after-fixup>
