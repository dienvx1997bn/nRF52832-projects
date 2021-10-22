
/** @file
 *
 * @defgroup blinky_example_main main.c
 * @{
 * @ingroup blinky_example
 * @brief Blinky Example Application main file.
 *
 * This file contains the source code for a sample application to blink LEDs.
 *
 */

#include <stdbool.h>
#include <stdint.h>
#include "nrf_delay.h"

#define GPIO_PIN_CNF_OFFSET		0x700
#define GPIO_PIN_OUTSET_OFFSET	0x508
#define GPIO_PIN_OUTCLR_OFFSET	0x50C

static volatile uint8_t *GPIO = (uint8_t *)0x50000000UL;

/*
*	pin_num:		gpio number
*	pin_mode_pull:	0-no pull; 1-pull down; 3-pull up
*/
void gpio_cfg_pin_out(uint8_t pin_num, uint8_t pin_mode_pull) {
	uint32_t off_set = GPIO_PIN_CNF_OFFSET + pin_num * 4;	//32bit registers
	*((uint32_t *)(GPIO + off_set)) = 	0x01 |				//config as out
										pin_mode_pull<< 2;	//pull mode
}

/*
*	pin_num:		gpio number
*	pin_level:		0-low; 1-high
*/
void gpio_cfg_pin_out_write(uint8_t pin_num, uint8_t pin_level) {
	if(pin_level) {
		*((uint32_t *)(GPIO + GPIO_PIN_OUTSET_OFFSET)) = 1<<pin_num;
	} else {
		*((uint32_t *)(GPIO + GPIO_PIN_OUTCLR_OFFSET)) = 1<<pin_num;
	}
}


/** * 4
 * @brief Function for application main entry.
 */
int main(void)
{
	uint8_t pin_num = 18;
	
	gpio_cfg_pin_out(pin_num, 0);
	
	while(true) {
		gpio_cfg_pin_out_write(pin_num, 0);
		nrf_delay_ms(500);
		gpio_cfg_pin_out_write(pin_num, 1);
		nrf_delay_ms(500);
	}
}

/**
 *@}
 **/
