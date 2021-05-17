#include "overflow.h"

#include <hidef.h>      /* common defines and macros */

#include "derivative.h"      /* derivative-specific definitions */


volatile unsigned int overflow_counter = 0;
volatile unsigned int timer = 0;


void InitialiseTimer(void) {
  
  TSCR1=0x90;
  TSCR2=0x80;   // prescaler 1, before 32 = 0x04
}


unsigned int GetOverflowCount(void) {
 return overflow_counter; 
}

void ResetOverflowCount(void) {
 overflow_counter = 0; 
}


// the interrupt for timer overflow 
#pragma CODE_SEG __NEAR_SEG NON_BANKED /* Interrupt section for this module. Placement will be in NON_BANKED area. */
__interrupt void OVERFLOW_ISR(void) { 

  overflow_counter += 1;   
  timer = TCNT;
}