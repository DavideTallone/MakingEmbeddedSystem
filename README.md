# Exercise 2.1 Idea project diagram
# What is this?
It is the concept for an autonomus blimp with thermal and video sensor, for wildfires early detection and prevention.

## What does it do?
It can roam in a predefined area, defined by gps coordinates, searching for hotspot in the vegetation, that could lead to a fire.\
When one such hotspot is detected, a ping is sent via radio to the human operator that can then take direct control of the drone to better investigate the situation. 


## Block diagram 
![Blimp](E2.1/Images/Ex%202.1%20-MakingEmbeddedSystems.png)



# Exercise 2.2 Read mbed code, make diagram
## What and why did you chose it?
I've chosen the EFM32 Zero Gecko, as it has the EFM32ZG-STK3200 MCU, which is based on the same M0+ cortex as the samd21j18A that I've selected for the final project.
Also, it was the only one in the M0+ family that I've found whith a template more complex than "blinken light" or "print a string through serial".

## Block diagram 
![Blimp](E2.2/Images/Ex%202.2%20-MakingEmbeddedSystems.png)
