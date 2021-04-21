#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */

#include "keypad.h"


void main(void) {

  /* put your own code here */
  volatile int is_being_pressed = 0;
  
  // could allocate memory here, then use this to pass to other functions
  struct KeypadConfig config;
  initialise_keypad(&config, (unsigned char*)(0x32));
  
  config.status.bits.initialised = 0;
  config.status.bits.initialised = 1;
  
  config.status.bits.any_pressed = 0;
  config.status.bits.any_pressed = 1;
    
  // using the memory allocated in the private scope of keypad.c   
  EnableInterrupts;


  for(;;) {
    keypad_check(&config);
    
    if (config.currently_pressed == BUTTON_UP) {
      // do something here
      is_being_pressed = BUTTON_UP;
    } 
    
    _FEED_COP(); /* feeds the dog */
  } /* loop forever */
  /* please make sure that you never leave main */
}
