#include "timers.h"

// include the register/pin definitions
#include "derivative.h"      /* derivative-specific definitions */


void Init_TC7 (void) {
  // set up the timers for channel 7 to use the interrupt
  TSCR1=0x90;
  TSCR2=0x04;
  TIOS=TIOS | TIOS_IOS7_MASK;
  TCTL1=0x40;
  TIE=0x80;
}


// look at the isr_vectors.c for where this function is 
//  added to the ISR vector table
#pragma CODE_SEG __NEAR_SEG NON_BANKED /* Interrupt section for this module. Placement will be in NON_BANKED area. */
__interrupt void TC7_ISR(void) { 
  
  TC7 =TCNT + (word)62500;    // 12 Hhz and PT7
  TFLG1=TFLG1 | TFLG1_C7F_MASK;
  PORTB=0xF0;        // High nibble LED on
}
