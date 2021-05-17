#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */

#include "overflow.h"



void main(void) {
  /* put your own code here */

  volatile unsigned int keep_counting = 0;

  InitialiseTimer();
  

	EnableInterrupts;
	COPCTL = 7;


  for(;;) {
    keep_counting = GetOverflowCount();
    _FEED_COP(); /* feeds the dog */
  } /* loop forever */
  /* please make sure that you never leave main */
}
