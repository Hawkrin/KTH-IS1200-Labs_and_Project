/* Alot of the code in the file is taken from mipslabwork.c
  which is written 2015 by F Lundevall
  and updated 2017-04-21 by F Lundevall
  and modified 2017-04-31 by Ture Teknolog 
  and modified by Harry Lazaridis and Malcolm Liljedahl 2021

   For copyright and licensing, see file COPYING */

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <stdlib.h>
#include <stdio.h>
#include "includes/registers.h"  /* Declarations of system-specific addresses etc */
#include "includes/mipslab.h"  /* Declatations for these labs */
#include "includes/io.h"

#define HEIGHT 32
#define WIDTH 128
#define TIMER2 ((80000000 / 256) / 10); //Timer 2 initialization, 100ms.
#define TIMER3 ((80000000 / 256)); //Timer 3 initialization, 1s.

void show_fruit(int value);              

uint8_t points = 0;

int fruitX = 32;
int fruitY = 11;

int snakePosX = 10;
int snakePosY = 11;

int snakeXDir = 1;
int snakeYDir = 0;

int *tail;
int tailSize = 0;

int mytime = 0x0000;
int timeoutcount = 0;
int count = 0;
uint8_t seed = 0;


/* Interrupt Service Routine */
void user_isr( void )
{
  return;
}

void labinit( void )
{
  volatile int * E = (volatile int *) 0xbf886100;	

  *E = *E & 0xff00; //Sets the 8 leats sig bits as zero = output

  TRISD = TRISD & 0x0fe0;

  //TIMER 2 INIT
  T2CONSET = 0x70;   //Prescale 1:256
  PR2 = TIMER2;      //timeperiod
  TMR2 = 0;          //reset timer
  T2CONSET = 0x8000; //starting the timer

  //TIMER 3 INIT
  T3CONSET = 0x70;   //Prescale 1:256
	PR3 = TIMER3       //timeperiod
  TMR3 = 0x0;        //reset timer
	T3CONSET = 0x8000; //starting the timer


  return;
}
void next_pos_fruit(void) {
  
  int x = ((seed * 123) % 120) + 1; 
  int y = ((seed * 21) % 20) + 1;
  
  show_fruit(0);

  fruitX = x;
  fruitY = y;

  show_fruit(1);

  points++;
}


void show_fruit(int value)
{
  screen[fruitY * 128 + (fruitX)] = value;
  screen[fruitY * 128 + (fruitX) + 1] = value;
  screen[(fruitY + 1) * 128 + (fruitX)] = value;
  screen[(fruitY + 1) * 128 + (fruitX) + 1] = value;
}

void show_snake(int value) {
  screen[snakePosY * 128 + (snakePosX)] = value;
  screen[snakePosY * 128 + (snakePosX) + 1] = value;
  screen[(snakePosY + 1) * 128 + (snakePosX)] = value;
  screen[(snakePosY + 1) * 128 + (snakePosX) + 1] = value;

  int tempX;
  int tempY;

  if (tailSize > 0) {
    int i;
    for (i = 0; i < tailSize; i++) {
        
        tempX = tail[i] >> 5;
        tempY = tail[i] & 31;

        screen[tempY * 128 + (tempX)] = value;
        screen[tempY * 128 + (tempX) + 1] = value;
        screen[(tempY + 1) * 128 + (tempX)] = value;
        screen[(tempY + 1) * 128 + (tempX) + 1] = value;
    }
  }
}


void increment_tail(void) {
  int newTail[tailSize + 1];
  int i;

  if (tailSize > 0) {
    for (i = 0; i < (tailSize - 2); i++) {
      newTail[i] = tail[i + 1];
    }
  }

  newTail[tailSize] = (snakePosX << 5) + snakePosY; 
  tailSize++;
  tail = newTail;
}

void collision_detection(void) {
  //Collition with fruit
  if((snakePosX == fruitX || snakePosX == fruitX) && (snakePosY == (fruitY) || snakePosY == fruitY)) { 
    next_pos_fruit();
    increment_tail();
  } 

  //Wall detection
  if(snakePosX < 1 || snakePosX > 127 || snakePosY < 1 || snakePosY > 31) {
  }
}

void update_snake(void) {
  show_snake(0);

  if (tailSize > 0) {
    tail[0] = (snakePosX << 5) + snakePosY;

    int i;
    for (i = 1; i < (tailSize); i++) {
      tail[i] = tail[i + 1];
    }
  }

  snakePosX += snakeXDir;
  snakePosY += snakeYDir;

  seed++;
}

//Movement
void update_snake_pos(void) {
  //Move snake to right
  if (get_btns() & 0b0001) {
    snakeXDir = 1;
    snakeYDir = 0;
  } 
  //Move snake upwards
  if (get_btns() & 0b0010) {
    snakeXDir = 0;
    snakeYDir = -1;
  }
  //Move snake downwards
  if (get_btns() & 0b0100) {
    snakeXDir = 0;
    snakeYDir = 1;
  }
  //Move snake upwards
  if (get_btns() & 0b1000) {
    snakeXDir = -1;
    snakeYDir = 0;
  }
}

/* This function is called repetitively from the main program */
void labwork( void )
{
  
  if (seed == (sizeof(uint8_t) * 256) - 1) { seed = 0; }
  volatile int* porte = (volatile int *) 0xbf886110;


  int s = get_sws();
  int b = get_btns();

  set_LEDs(points);


  if (IFS(0) & 0x100) {  //checks the timeout flag event
	
    IFSCLR(0) = 0x100;  //resets all event flags
    timeoutcount++;
    count ++;
    seed++;

    if (timeoutcount == 2) {
      seed++;

      set_LEDs(points);
      display_render();
      show_fruit(1);
      update_snake();
      show_snake(1);
      update_snake_pos();
      collision_detection();
    

      timeoutcount = 0;

      display_render();
    }
  }
 
}
