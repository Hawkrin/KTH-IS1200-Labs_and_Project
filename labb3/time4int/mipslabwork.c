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

#define TIMER2 ((80000000 / 256) / 10);

int prime = 1234567;
int mytime = 0x0000;
int timeoutcount = 0;

char textstring[] = "text, more text, and even more text!";
char test[] = "test";

/* Interrupt Service Routine */
void user_isr( void ) {  


  if (IFS(0) & 0x100) { //check timeout event

    IFSCLR(0) = 0x100; //reset flag events
    timeoutcount++;

    if (timeoutcount == 10) {
      time2string( textstring, mytime );  
      display_string( 3, textstring );  
      display_update();  
      tick( &mytime );

      timeoutcount = 0;
    }
  }
}

/* Lab-specific initialization goes here */
void labinit( void )
{
  volatile int * E = (volatile int *) 0xbf886100;	

  *E = *E & 0xff00; //Sets the 8 leats sig bits as zero = output

  TRISD = TRISD & 0x0fe0;

  T2CONSET = 0x70; //Prescale 1:256
  PR2 = TIMER2;
  TMR2 = 0;
  T2CONSET = 0x8000; //turn time.

  
	// Enable interrupts from TMR2

	//Configures the priority(0-7)
  IPC(2) = 4; //Interupt Priority Controll

            //sets the bit for the interupt we want to enable
	IEC(0) = 0x100; //Interupt Enable Controll
	// Enable interrupts for SW3
	IPC(3) = 0x1c000000;
	IEC(0) = IEC(0) | (1 << 15);	

 	 enable_interrupt(); // interrupts are enabled globaly

  return;
}

/* This function is called repetitively from the main program */
void labwork( void ) {  
  prime = nextprime( prime );  
  display_string( 0, itoaconv( prime ) );  
  display_update();}
}
