#ifndef KEYPAD_HEADER
#define KEYPAD_HEADER

// public interface
typedef enum {
    BUTTON_NONE=0x0,    // no button
    BUTTON_UP=0x2,      // button K1
    BUTTON_LEFT=0x4,    // button K4
    BUTTON_RIGHT=0x6,   // button K6
    BUTTON_DOWN=0x8,    // button K9
    BUTTON_INVALID=0xFF
} BUTTON_DIRECTION;

typedef enum {
    KEYPAD_PORTK=0x0,    // port k keypad
    KEYPAD_PORTJ=0x1     // port j keypad
} KEYPAD_HARDWARE;


                        
  
struct KeypadConfig {

  BUTTON_DIRECTION currently_pressed, previous_button;
  BUTTON_DIRECTION button_press_buffer[16];

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


#endif