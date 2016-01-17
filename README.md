# avr_msp_rotate_shift

The least number of instructions needed for rotate shift. It means rotating shift <b>right</b> if x is positive, otherwise rotating shift left. The red pointers is the basic operations which can not be implemented by others. For example, <i>rotate shift left by 2 bits</i> can be implemented using <i>rotate shift left by 1 bit</i> twice. But it can not be done in turn.<br><br>

### Results for 16-bit block on AVR
![rotate shift for 16-bit block on AVR](./pic/avr_results.png?raw=true)<br>

### Results for 16-bit block on MSP
![rotate shift for 16-bit block on MSP](./pic/msp_results.png?raw=true)<br>

