/**
 * \file button.c
 *
 * \brief This file hold the button initialization routines and ISR callbacks
 *
 */

#include <asf.h>
#include "Button.h"
#include "Timer.h"

/* void configure_extint_channel(void)
 *	\brief configure button interrupt
 */
void configure_extint_channel(void)
{
	struct extint_chan_conf config_extint_chan;
	extint_chan_get_config_defaults(&config_extint_chan);
	config_extint_chan.gpio_pin           = BUTTON_0_EIC_PIN;
	config_extint_chan.gpio_pin_mux       = BUTTON_0_EIC_MUX;
	config_extint_chan.gpio_pin_pull      = EXTINT_PULL_UP;
	config_extint_chan.detection_criteria = EXTINT_DETECT_BOTH;
	extint_chan_set_config(BUTTON_0_EIC_LINE, &config_extint_chan);
}

/* void configure_extint_callbacks(void)
 *	\brief configure button interrupt callback
 */
void configure_extint_callbacks(void)
{

	extint_register_callback(extint_detection_callback,	BUTTON_0_EIC_LINE,EXTINT_CALLBACK_TYPE_DETECT);
	extint_chan_enable_callback(BUTTON_0_EIC_LINE,EXTINT_CALLBACK_TYPE_DETECT);

}

/* void extint_detection_callback
 *	\brief configure button interrupt callback
 */
void extint_detection_callback(void)
{
	TIMER_enableDebouncer(true);
	return;
}

