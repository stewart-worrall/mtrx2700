#ifndef OVERFLOW_HEADER
#define OVERFLOW_HEADER


__interrupt void OVERFLOW_ISR(void);


unsigned int GetOverflowCount(void);
void ResetOverflowCount(void);
                    
void InitialiseTimer(void);


#endif
