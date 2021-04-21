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



// get access to the keypad data structures hidden in the c file
void initialise_all_keypads(void);

// find if a specific keypad is being pressed 1 = pressed, 0 = not pressed
int is_keypad_pressed(KEYPAD_HARDWARE keypad);


#endif