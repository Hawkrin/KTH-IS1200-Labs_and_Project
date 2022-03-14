/* mipslabwork.c

   This file written 2015 by F Lundevall
   Updated 2017-04-21 by F Lundevall

   This file should be changed by YOU! So you must
   add comment(s) here with your name(s) and date(s):

   This file modified 2017-04-31 by Ture Teknolog 

   For copyright and licensing, see file COPYING */

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "mipslab.h"  /* Declatations for these labs */

#define TIMER2 ((80000000 / 256) / 10); //Timer 2 initialization, 100ms.
			                   // 80MHz, 1:256 prescaler

int mytime = 0x0000;
int timeoutcount = 0;

char textstring[] = "text, more text, and even more text!";
char test[] = "test";

/* Interrupt Service Routine */
void user_isr( void )
{
  return;
}

/* Lab-specific initialization goes here */
void labinit( void )
{
  volatile int * E = (volatile int *) 0xbf886100;	

  *E = *E & 0xff00; //Sets the 8 leats sig bits as zero = output

  TRISD = TRISD & 0x0fe0;

  T2CONSET = 0x70; //Prescale 1:256
  PR2 = TIMER2; //timeperiod
  TMR2 = 0; //reset timer
  T2CONSET = 0x8000; //starting the timer

  return;
}

/* This function is called repetitively from the main program */
void labwork( void )
{
  volatile int* porte = (volatile int *) 0xbf886110;

  (*porte) += 0x1; 


  int s = getsw();
  int b = getbtns();

  if (b & 4) {
	mytime = (mytime & 0x0fff) | (s << 12);
  }
  
  if (b & 2) {
	mytime = (mytime & 0xf0ff) | (s << 8);
  }

  if (b & 1) {
	mytime = (mytime & 0xff0f) | (s << 4);
  }


  //display_debug(&IFS(0));

//  delay( 1000  );
  
  if (IFS(0) & 0x100) {  //checks the timeout flag event
	
    IFSCLR(0) = 0x100;  //resets all event flags
    timeoutcount++;

    if (timeoutcount == 10) {

  	time2string( textstring, mytime );
  	display_string( 3, textstring );
  	display_update();
  	tick( &mytime );
 	  display_image(96, icon);
  
  	timeoutcount = 0;

    }
  }
 
}
