# avr_rotate_shift
Rotate shift left (or right) by several bit positions on AVR<br><br>

The least number of instructions needed for rotate shift. It means rotating shift <b>right</b> if x is positive, otherwise rotating shift left. The green numbers is the basic operations which can not be implemented by others. For example, <i>rotate shift left by 2 bit positions</i> can be implemented by 2 times of <i>rotate shift left by 1 bit position</i>. But it can not be done in turn.<br><br>

# Results for 32-bit block
![rotate shift for 32-bit block](./pic/bit32.png?raw=true)<br>

# Results for 16-bit block
![rotate shift for 16-bit block](./pic/bit16.png?raw=true)<br>

# msp_rotate_shift
Rotate shift left (or right) by several bit positions on MSP<br><br>

