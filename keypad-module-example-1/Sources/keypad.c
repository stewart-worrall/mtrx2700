#include "keypad.h"


void initialise_keypad(struct KeypadConfig *config, unsigned char* address) {
  config->keypad_register = address;
  config->status.register_value = 0x00;
  config->status.bits.initialised = 1;  
  config->status.bits.any_pressed = 0;  
}

                            
void keypad_check(struct KeypadConfig *config) {
  volatile int current_value = 0;
  current_value = *(config->keypad_register);
  
  if (current_value == 0) {
    config->status.bits.any_pressed = 0; 
  } else {
    config->status.bits.any_pressed = 1; 
  }
  
  if (current_value == BUTTON_NONE ||
      current_value == BUTTON_UP ||
      current_value == BUTTON_LEFT ||
      current_value == BUTTON_RIGHT ||
      current_value == BUTTON_DOWN) {
        
    config->previous_button = config->currently_pressed;
    config->currently_pressed = current_value;
      
  } else {
    config->currently_pressed = BUTTON_INVALID;
  }
}

