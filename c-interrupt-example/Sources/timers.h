#ifndef TIMERS_HEADER
#define TIMERS_HEADER


// function to initialise the timer
void Init_TC7 (void);

// Timer interrupt definition
__interrupt void TC7_ISR(void);


#endif
