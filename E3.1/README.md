# Exercise 3.1 Investigate project board
Look at the documents for the board you are considering for your final project (or any ST\
Discovery Board), draw the hardware block diagram for the board. For peripherals, note the\
communication paths (SPI, I2C, etc).

# What kind of processor is it
It is a SAMD21j18A produced by microchip, with an Arm Cortex-M0+ CPU running at up to 48 MHz.\
# How much Flash and RAM does it have? Any other memory type?
It has 256 Kbytes of internal Flash, and 32 KBytes of internal SRAM.
#Does it have any special peripherals?
It has one 2.0 USB interface that can be configured either as host or as slave.\
I found interesting that such a tiny an low power mcu can have usb host cabability,\
even if I plan to utilize it as slave.\

As my final project need to have a time stamp functionality, the Real Time Clock, in conjunction to\
one of the 5 16bit Timers/Counters, will sure come in handy.

I've also noticed the Event System, that, as written in the datasheet at page 388, "allows autonomous,\
low-latency and configurable communication between peripherals".

# Does it have a FPU?
No.

# If it has an ADC, what are the features?
From the datasheet at page 780:\
• 8-, 10- or 12-bit resolution\
• Up to 350,000 samples per second (350ksps)\
• Differential and single-ended inputs\
– Up to 32 analog input (note:20 for the SAMD21J18A)\
– 25 positive and 10 negative, including internal and external\
• Five internal inputs\
– Bandgap\
– Temperature sensor\
– DAC\
– Scaled core supply\
– Scaled I/O supply\
• 1/2x to 16x gain\
• Single, continuous and pin-scan conversion options\
• Windowing monitor with selectable channel\
• Conversion range:\
– Vref [1v to VDDANA - 0.6V]\
– ADCx * GAIN [0V to -Vref ]\
• Built-in internal reference and external reference options\
– Four bits for reference selection\
• Event-triggered conversion for accurate timing (one event input)\
• Optional DMA transfer of conversion result\
• Hardware gain and offset compensation\
• Averaging and oversampling with decimation to support, up to 16-bit result\
• Selectable sampling time


## Block diagram 
![HWDiag](E3.1/Images/BlockDiagram.png)


