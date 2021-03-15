#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */



void main(void) {
  /* put your own code here */
  
  volatile int x = 1, y = 2, z = 3;
    
  volatile float a = 0.1, b = 0.2, c = 0.3;
  
  volatile int answer_1 = 0;
  volatile float answer_2 = 0.0;
  
  answer_1 = x + y + z;
  answer_2 = a + b + c;
  
  

	EnableInterrupts;


  for(;;) {
    _FEED_COP(); /* feeds the dog */
  } /* loop forever */
  /* please make sure that you never leave main */
}
