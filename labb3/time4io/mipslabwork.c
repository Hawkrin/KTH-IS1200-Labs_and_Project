/* mipslabwork.c

   This file written 2015 by F Lundevall
   Updated 2017-04-21 by F Lundevall

   This file should be changed by YOU! So you must
   add comment(s) here with your name(s) and date(s):

   This file modified 2017-04-31 by Ture Teknolog 

   For copyright and licensing, see file COPYING */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "mipslab.h"  /* Declatations for these labs */

int mytime = 0x0000;

char textstring[] = "text, more text, and even more text!";

/* Interrupt Service Routine */
void user_isr( void )
{
  return;
}

/* Lab-specific initialization goes here */
void labinit( void )
{
  volatile int * E = (volatile int *) 0xbf886100; // E points to address of TRISE -> initializing

  *E = *E & 0xff00; //Sets the 8 last bits to 0, OUTPUT

  TRISD = TRISD & 0x0fe0; //initializes port D, bit 11-5 are set as inputs.

  return;
}

/* This function is called repetitively from the main program */
void labwork( void )
{
  volatile int* porte = (volatile int *) 0xbf886110; // porte points to address of PORTE	

  (*porte) += 0x1; //increments the pointer by 1 which is shown by the LEDS on the chipkit

  int s = getsw();
  int b = getbtns();

//"updates"  the variable mytime by pressing buttons.
  if (b & 4) {
	mytime = (mytime & 0x0fff) | (s << 12);
  }
  
  if (b & 2) {
	mytime = (mytime & 0xf0ff) | (s << 8);
  }

  if (b & 1) {
	mytime = (mytime & 0xff0f) | (s << 4);
  }


  delay( 1000  );
  time2string( textstring, mytime );
  display_string( 3, textstring );
  display_update();
  tick( &mytime );
  display_image(96, icon);
}
