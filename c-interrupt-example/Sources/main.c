#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */

#include "timers.h"

void main(void) {
  // demonstration of the difference with/without volatile
  //  look at the disassembled version of this code
  int x = 1, y = 2;
  int z = x + y;

  volatile int a = 1, b = 2;
  volatile int c = a + b;

  // set the ports for the LEDs
  DDRB= 0xFF;   /* Port B output */
  DDRJ= 0xFF;   // Port J to Output
  PTJ = 0x00;   // enable LEDs
 
  PORTB=0x0F;     // debugging info
 
  // call the initise timer function
  Init_TC7();
 
  // enable the interrupts
	// calls asm("CLI");
	EnableInterrupts;
  
  for(;;) {
    _FEED_COP(); /* feeds the dog */
  } /* loop forever */
  /* please make sure that you never leave main */
}





