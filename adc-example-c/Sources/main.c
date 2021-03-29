//Displaying ATD0 channel 7 (POT) on LEDs of PORTB in C Language for Dragon12+ Trainer Board 
//with HCS12 Serial Monitor Program installed. This code is for CodeWarrior IDE
//Modified from Program 13-1C of HCS12 book by Mazidi & Causey 
//In Dragon12+ PLL=48MHz. 48MHz/2=24MHz, Divivde by 24 to get 1MHz for conversion freq. 
//ATD0 channel 7 (AN07) is connected to VR2 Pot Trimer (above right side of breadboard)
//Change the POT to see the changes on LEDs of PORTB
 
#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */


void MSDelay(unsigned int);
void main(void) 
 {
  /* put your own code here */
  
    

    DDRB = 0xFF;    //PORTB as output
    DDRJ = 0xFF;    //PTJ as output for Dragon12+ LEDs
    PTJ=0x0;        //Allow the LEDs to dsiplay data on PORTB pins
    
    ATD0CTL2 = 0x80;     //Turn on ADC,..No Interrupt
    MSDelay(1);	      //optional 	
    ATD0CTL3 = 0x08;  //one conversion, no FIFO
    ATD0CTL4 = 0xEB;  //8-bit resolu, 16-clock for 2nd phase,
                      //prescaler of 24 for Conversion Freq=1MHz  
    for(;;)
    {
      ATD0CTL5 = 0x87;  //Channel 7 (right justified, unsigned,single-conver,one chan only) 
		  // change this value for other channels.

      while(!(ATD0STAT0 & 0x80));
      PORTB = ATD0DR0L;  //dump it on LEDs
    
      //MSDelay(250);     /optional
    }
    

  }

 void MSDelay(unsigned int itime)
  {
    unsigned int i; unsigned int j;
    for(i=0;i<itime;i++)
      for(j=0;j<4000;j++);
  }