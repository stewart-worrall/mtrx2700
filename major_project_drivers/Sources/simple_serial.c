// simple serial interface

#include "simple_serial.h" 
#include "derivative.h"        /* derivative information */



// initialise SCI1
void SCI1_Init(unsigned short baudRate) {
  
  SCI1BDH = 0;

  switch(baudRate){
	case BAUD_300:
	  SCI1BDH=19;
  	SCI1BDL=136;
	  break;
	case BAUD_600:
	  SCI1BDH=9;
  	SCI1BDL=196;
	  break;
	case BAUD_1200:
	  SCI1BDH=4;
  	SCI1BDL=226;
	  break;
	case BAUD_2400:
	  SCI1BDH=2;
  	SCI1BDL=113;
	  break;
	case BAUD_4800:
    SCI1BDH=1;
    SCI1BDL=56;
	  break;
	case BAUD_9600:
    SCI1BDH=0;
    SCI1BDL=156;
	  break;
	case BAUD_19200:
    SCI1BDH=0;
    SCI1BDL=78;
	  break;
	case BAUD_38400:
    SCI1BDH=0;
    SCI1BDL=39;
	  break;
	case BAUD_57600:
    SCI1BDH=0;
    SCI1BDL=26;
	  break;
	case BAUD_115200:
    SCI1BDH=0;
    SCI1BDL=13;
	  break;
  }
  

  SCI1CR1 = 0;
  SCI1CR2 = 0x0C; 
}
    
        
// Output single character
void SCI1_OutChar(char data) {
 
  while((SCI1SR1 & SCI1SR1_TDRE_MASK) == 0){};
  SCI1DRL = data;  
}



#define NULL_CHARACTER 0x00

// Output null terminated string 
void SCI1_OutString(char *buffer) {

  while(*buffer) {
  
    SCI1_OutChar(*buffer);
    buffer++; 
  }  
}


