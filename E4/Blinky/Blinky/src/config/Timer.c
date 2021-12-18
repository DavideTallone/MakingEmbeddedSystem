/**
 * \file Timer.c
 *
 * \brief This file hold the Timer initialization routines and ISR callbacks
 *
 */
#include <asf.h>
#include "Timer.h"

#define CONF_TC_MODULE TC3

/*debouncer states*/
#define STATE_IDLE_LOW	0
#define STATE_DONE_DEBOUNCING 1
#define STATE_IDLE_HIGH 2

static volatile bool isDebouncerEnabled=false;	//set by interrupt callback

struct tc_module tc_instance;

/* void TIMER_enableDebouncer(bool ena)
 *	\brief Enable or disable the debouncer
 */
void TIMER_enableDebouncer(bool ena){
	isDebouncerEnabled=ena;
}

/* void tc_callback_to_toggle_led(struct tc_module *const module_inst)
 *	\brief callback called every time the timer 3 interrupt is fired
 */

void tc_callback_to_toggle_led(struct tc_module *const module_inst){
	if(!isDebouncerEnabled){return;}				//Button interrupt has not been fired, do nothing and return
	static int8_t ButtonReadCount=0;			//this variable is used to keep track of the debouncing state
	
	if(ButtonReadCount==STATE_DONE_DEBOUNCING){
		port_pin_toggle_output_level(LED0_PIN);
		isDebouncerEnabled=false;}
	if(!port_pin_get_input_level(BUTTON_0_PIN)){
		if(ButtonReadCount<STATE_IDLE_HIGH)ButtonReadCount++;}
	else {
		if(ButtonReadCount>STATE_IDLE_LOW) ButtonReadCount--;}
		
	return;
}

/* void configure_tc_callbacks(void)
 *	\brief Configuration function for the timer callback 
 */
void configure_tc_callbacks(void)
{
	tc_register_callback(&tc_instance, tc_callback_to_toggle_led,
	TC_CALLBACK_OVERFLOW);
	tc_register_callback(&tc_instance, tc_callback_to_toggle_led,
	TC_CALLBACK_CC_CHANNEL0);
	tc_register_callback(&tc_instance, tc_callback_to_toggle_led,
	TC_CALLBACK_CC_CHANNEL1);
	tc_enable_callback(&tc_instance, TC_CALLBACK_OVERFLOW);
	tc_enable_callback(&tc_instance, TC_CALLBACK_CC_CHANNEL0);
	tc_enable_callback(&tc_instance, TC_CALLBACK_CC_CHANNEL1);
	return;
}

/* void configure_tc(void)
 *	\brief timer configuration function
 */

void configure_tc(void)
{
	struct tc_config config_tc;
	tc_get_config_defaults(&config_tc);
	config_tc.counter_size = TC_COUNTER_SIZE_8BIT;			//8bit timer	
	config_tc.clock_source = GCLK_GENERATOR_0;				//Timer clock derived from 1MHz main CLK

	config_tc.clock_prescaler = TC_CLOCK_PRESCALER_DIV1024;	//prescaler divide Tclock by 1024
	config_tc.counter_8_bit.period = 244;					//top count set to 8
	tc_init(&tc_instance, CONF_TC_MODULE, &config_tc);		
	tc_enable(&tc_instance);
	return;
}