// filename  ***************  sci1.c ****************************** 
// Simple I/O routines to 9S12C32 serial port   
// Jonathan W. Valvano 1/29/04

//  This example accompanies the books
//   "Embedded Microcomputer Systems: Real Time Interfacing",
//         Brooks-Cole, copyright (c) 2000,
//   "Introduction to Embedded Microcomputer Systems: 
//    Motorola 6811 and 6812 Simulation", Brooks-Cole, copyright (c) 2002

// Copyright 2004 by Jonathan W. Valvano, valvano@mail.utexas.edu 
//    You may use, edit, run or distribute this file 
//    as long as the above copyright notice remains 
// Modified by EE345L students Charlie Gough && Matt Hawk
// Modified by EE345M students Agustinus Darmawan + Mingjie Qiu
//
// adapted to the Dragon12 board using SCI1            --  fw-07-04
// allows for 24 MHz bus (PLL) and 4 MHz bus (no PLL)  -- fw-07-04
 
#include <mc9s12dp256.h>        /* derivative information */
#include "sci1.h"
//#include "pll.h"                /* macro _SYSCLOCK */

#define RDRF 0x20   // Receive Data Register Full Bit
#define TDRE 0x80   // Transmit Data Register Empty Bit


//-------------------------SCI1_Init------------------------
// Initialize Serial port SCI1
// Input: baudRate is tha baud rate in bits/sec
// Output: none
void SCI1_Init(unsigned short baudRate) {
  
  SCI1BDH = 0;   // br=MCLK/(16*baudRate) 
  
  /* check if bus frequency has been boosted to 24 MHz (fw-07-04) */
  /* 24 MHz bus frequency (PLL is used, SYNR = 2, REFDV = 0 -> factor 6)
     Baud rate generator: SCI1BDL/H = (24e6/16)/baudrate = 1.5e6/baudrate */
  switch(baudRate){
	case BAUD_300:
	  SCI1BDH=19;
  	  SCI1BDL=136;
	  break;
	case BAUD_600:
	  SCI1BDH=9;
  	  SCI1BDL=196;
	  break;
	case BAUD_1200:
	  SCI1BDH=4;
  	  SCI1BDL=226;
	  break;
	case BAUD_2400:
	  SCI1BDH=2;
  	  SCI1BDL=113;
	  break;
	case BAUD_4800:
      SCI1BDH=1;
      SCI1BDL=56;
	  break;
	case BAUD_9600:
      SCI1BDH=0;
      SCI1BDL=156;
	  break;
	case BAUD_19200:
      SCI1BDH=0;
      SCI1BDL=78;
	  break;
	case BAUD_38400:
      SCI1BDH=0;
      SCI1BDL=39;
	  break;
	case BAUD_57600:
      SCI1BDH=0;
      SCI1BDL=26;
	  break;
	case BAUD_115200:
      SCI1BDH=0;
      SCI1BDL=13;
	  break;
  }

  SCI1CR1 = 0;
/* bit value meaning
    7   0    LOOPS, no looping, normal
    6   0    WOMS, normal high/low outputs
    5   0    RSRC, not appliable with LOOPS=0
    4   0    M, 1 start, 8 data, 1 stop
    3   0    WAKE, wake by idle (not applicable)
    2   0    ILT, short idle time (not applicable)
    1   0    PE, no parity
    0   0    PT, parity type (not applicable with PE=0) */ 
  SCI1CR2 = 0x0C; 
/* bit value meaning
    7   0    TIE, no transmit interrupts on TDRE
    6   0    TCIE, no transmit interrupts on TC
    5   0    RIE, no receive interrupts on RDRF
    4   0    ILIE, no interrupts on idle
    3   1    TE, enable transmitter
    2   1    RE, enable receiver
    1   0    RWU, no receiver wakeup
    0   0    SBK, no send break */ 

}
    
        
//-------------------------SCI1_OutChar------------------------
// Wait for buffer to be empty, output 8-bit to serial port
// busy-waiting synchronization
// Input: 8-bit data to be transferred
// Output: none
void SCI1_OutChar(char data) {
 
  while((SCI1SR1 & TDRE) == 0){};
  SCI1DRL = data;
                
}



//-------------------------SCI1_OutString------------------------
// Output String (NULL termination), busy-waiting synchronization
// Input: pointer to a NULL-terminated string to be transferred
// Output: none
void SCI1_OutString(char *pt, int length) {

  while(length > 0) {
  
    SCI1_OutChar(*pt);
    pt++;
    length--;
  }            
}




