/**
 * \file
 *
 * \brief Empty user application template
 *
 */

/**
 * \mainpage User Application template doxygen documentation
 *
 * \par Empty user application template
 *
 * This is a bare minimum user application template.
 *
 * For documentation of the board, go \ref group_common_boards "here" for a link
 * to the board-specific documentation.
 *
 * \par Content
 *
 * -# Include the ASF header files (through asf.h)
 * -# Minimal main function that starts with a call to system_init()
 * -# Basic usage of on-board LED and button
 * -# "Insert application code here" comment
 *
 */

#include <asf.h>
#define CONF_TC_MODULE TC3

#define STATE_IDLE_LOW 0
#define STATE_DONE_DEBOUNCING 1
#define STATE_IDLE_HIGH 2
#define HIGH_TO_LOW		1
#define LOW_TO_HIGH		0

struct tc_module tc_instance;

void tc_callback_to_toggle_led(struct tc_module *const module_inst){

	static int8_t ButtonReadCount=0;
	
	if(ButtonReadCount==STATE_DONE_DEBOUNCING){port_pin_toggle_output_level(LED0_PIN);}
	if(!port_pin_get_input_level(BUTTON_0_PIN)){
		if(ButtonReadCount<STATE_IDLE_HIGH)ButtonReadCount++;}
	else {
		if(ButtonReadCount>STATE_IDLE_LOW) ButtonReadCount--;}
		
	return;
}

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

void configure_tc(void)
{
	struct tc_config config_tc;
	tc_get_config_defaults(&config_tc);
	config_tc.counter_size = TC_COUNTER_SIZE_8BIT;
	config_tc.clock_source = GCLK_GENERATOR_0;

	config_tc.clock_prescaler = TC_CLOCK_PRESCALER_DIV1024;
	config_tc.counter_8_bit.period = 8;
	config_tc.counter_8_bit.compare_capture_channel[0] = 50;
	config_tc.counter_8_bit.compare_capture_channel[1] = 54;
	tc_init(&tc_instance, CONF_TC_MODULE, &config_tc);
	tc_enable(&tc_instance);
	return;
}


void configure_extint_channel(void);
void configure_extint_callbacks(void);
void extint_detection_callback(void);


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


void configure_extint_callbacks(void)
{

	extint_register_callback(extint_detection_callback,	BUTTON_0_EIC_LINE,EXTINT_CALLBACK_TYPE_DETECT);
	extint_chan_enable_callback(BUTTON_0_EIC_LINE,EXTINT_CALLBACK_TYPE_DETECT);

}

void extint_detection_callback(void)
{
	#ifdef NO_DEBOUNCE
	bool pin_state = port_pin_get_input_level(BUTTON_0_PIN);
	port_pin_set_output_level(LED_0_PIN, pin_state);
	#else

	#endif
}

int main (void)
{
	system_init();
	
    configure_tc();
    configure_tc_callbacks();


	while (1);
}
