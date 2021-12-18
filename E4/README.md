# Exercise 4 Blinky
On your final project board, make blinky for yourself. Then add a button to turn the LED on and off. Bonus points for making the button cause an interrupt.\
Triple bonus points for debouncing the button signal.

What are the hardware registers that cause the LED to turn on and off? (From the processor manual, don’t worry about initialization.) What are the button registers that you read? Can you read that memory directly and see the button change in a debugger or by printing out the associated memory?

Turn in your code with a comment or additional file answering the questions.

## What are the hardware registers that cause the LED to turn on and off?
REG_PORT_DIR1, to set the direction (in my particular case, to set LED0 as output, REG_PORT_DIR1|=0x40000000)\
REG_PORT_OUT1, to actually set the output level of the pin\
in my case:\
REG_PORT_OUT1 &= ~0x4000000; to set the led\
REG_PORT_OUT1 |= 0x4000000; to clear the led

REG_PORT_DIR1 memory location is 0x41004480\
REG_PORT_OUT1 memory location is 0x41004490

## What are the button registers that you read? 
Button state is kept in REG_PORT_IN0,  15th bit (0 indexed)\
REG_PORT_IN0 memory location is 0x41004420.

## Can you read that memory directly and see the button change in a debugger or by printing out the associated memory
Yes, to do that under the Microchip studio IDE for my board, go to Debug -> Windows -> I/O and click it.\
A new tab will be opened; There, choose the peripheral that your register belong to (IE PORT Module for LED and BUTTON in this application)

## Code
I've uploaded the full Microchip studio solution. Source code is under\
https://github.com/DavideTallone/MakingEmbeddedSystem/tree/main/E4/Blinky/Blinky/src
