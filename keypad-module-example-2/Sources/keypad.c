#include "keypad.h"



struct KeypadConfig {

  BUTTON_DIRECTION currently_pressed, previous_button;
  
  BUTTON_DIRECTION buffer[32];

  unsigned char *keypad_register; // the register containing the keypad

  union {
    unsigned char register_value;
    struct {
      unsigned char initialised :1;  // 1 for initialised, 0 for not initialised
      unsigned char any_pressed :1; // 1 for pressed, 0 for not pressed
    } bits;
  } status;
};


// function to initialise a keypad structure
void initialise_keypad(struct KeypadConfig *config, unsigned char* address);

// function to check the current state of a keypad (from a pointer)
void keypad_check(struct KeypadConfig *config);


// get access to the keypad data structures hidden in the c file
struct KeypadConfig* get_keypad(KEYPAD_HARDWARE keypad);






// private interface
// or, we can create the memory here (private), then use accessor functions to get access
#define NUMBER_OF_KEYPADS 2
struct KeypadConfig config[NUMBER_OF_KEYPADS];



struct KeypadConfig* get_keypad(KEYPAD_HARDWARE keypad) {
  return &config[keypad];
}


void initialise_keypad(struct KeypadConfig *config, unsigned char* address) {
  config->keypad_register = address;
  config->status.register_value = 0x00;
  config->status.bits.initialised = 1;  
  config->status.bits.any_pressed = 0;  
}


void initialise_all_keypads(void){
  initialise_keypad(&config[KEYPAD_PORTK], (unsigned char*)(0x32));
  initialise_keypad(&config[KEYPAD_PORTJ], (unsigned char*)(0x33));
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



int is_keypad_pressed(KEYPAD_HARDWARE keypad) {
   keypad_check(&config[keypad]);
   
   return config[keypad].currently_pressed; 
}

