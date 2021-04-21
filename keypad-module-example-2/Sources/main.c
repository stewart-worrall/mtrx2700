#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */

#include "keypad.h"

void main(void) {

  volatile int is_being_pressed;

  // using the memory allocated in the private scope of keypad.c
  initialise_all_keypads();

  EnableInterrupts;

  for(;;) {

    if (is_keypad_pressed(KEYPAD_PORTK) == BUTTON_UP) {
      // do something here
      is_being_pressed = BUTTON_NONE;
    } 
      
    _FEED_COP(); /* feeds the dog */
  } /* loop forever */
  /* please make sure that you never leave main */
}
