#include <stdint.h>
#include "includes/registers.h"

/* REGISTERS:
     x -> the port
    PORTx  -> register for writing(if output) or reading(if input)
    TRISx -> tells if the port is an input(1) or an output(0)
*/

/*

BTN1:
	pin #4 on UNO 32
	port RF1  -> TRISF, PORTF, bit index 1
BTN2:
	pin #34 on UNO 32
	port RD5  -> TRISD, PORTD, bit index 5
BTN3:
	pin #36 on UNO 32
	port RD6 -> TRISD, PORTD, bit index 6
BTN4:
	pin #37 on UNO 32
	port RD7 -> TRISD, PORTD, bit index 7
*/

/*

SW1:
    pin #2 on UNO 32
	port RD8  -> TRISD, PORTD, bit index 8
SW2:
    pin #7 on UNO 32
	port RD9  -> TRISD, PORTD, bit index 9
SW3:
    pin #8 on UNO 32
	port RD10  -> TRISD, PORTD, bit index 10
SW4:
    pin #35 on UNO 32
	port RD11  -> TRISD, PORTD, bit index 11
*/


//Initializes IO
void init_io()
{
    PORTE    = 0x0;
    TRISFSET = 0x2;   //Buttons 1
    TRISDSET = 0xE0;  //Buttons 2-4
    TRISDSET = 0xF00; //Switches 1-4
    TRISECLR = 0xFF;  //LEDs 1-8
	
}

//Gets buttons
uint8_t get_btns()
{
    uint8_t button1 = PORTF >> 1; //Btn 1
    button1 &= 0x1;               // masking
                
    uint8_t buttons = PORTD >> 4; //Btn 2-4
    buttons &= 0xE;               // masking
    
    buttons |= button1;
    return buttons;
}

//Gets switches
uint8_t get_sws()
{
    uint8_t switches = PORTD >> 8; //Sws 1-4
    switches &= 0xf;               // masking

    return switches;
}

//returns switches and/or buttons
uint8_t get_inputs()
{
    return (get_sws() << 4) | get_btns();
}

//Sets LEDs
void set_LEDs(uint8_t leds)
{
    PORTE = leds;
}
