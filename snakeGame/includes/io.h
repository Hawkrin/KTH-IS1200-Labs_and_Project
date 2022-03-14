#include <stdint.h>

#ifndef _IO_H_
#define _IO_H_


/**
 * Initialize buttons and switches
*/
void init_io();

/**
 * Returns values from all the switches
*/
uint8_t get_sws();

/**
 * Returns values from buttons.
*/
uint8_t get_btns();

/**
* Returns switches and buttons
*/
uint8_t get_inputs();

void setLEDs(uint8_t leds);

#endif