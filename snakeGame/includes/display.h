#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdint.h>

void host_Init();
void dsp_Init();
void display_Update();
void put_Buffer(int cb, BYTE * rgbTx);
BYTE spi_Write(BYTE bVal);
void set_pixel(int x, int y, int state);



#endif
