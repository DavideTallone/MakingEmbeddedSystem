/**
 * \file main.c
 *
 * \brief Main file for Exercise 4 of Making Embedded Systems by Elecia White
 *			Goal of this application, is to toggle on/off a led after given a button press,
 *			Assignement require that button must be handled via interrupt, and that it must be debounced
 *
 */

#include <asf.h>
#include "Timer.h"
#include "Button.h"

int main (void)
{
	system_init();
	
    configure_tc();
    configure_tc_callbacks();
	configure_extint_channel();
	configure_extint_callbacks();

	while (1);
}
