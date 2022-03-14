#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h"

//last 4 bits contains our wanted value
int getsw(void) {
	return (PORTD >> 8) & 0x000f; //shift the return value 8 places and then mask it
}

//last 3 bits contains our wanted value
int getbtns(void) {
	return (PORTD >> 5) & 0x0007; //shift the return value 5 places and then mask it
}
