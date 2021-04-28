#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */

#include <stdio.h>
#include <stdlib.h>

#include "sci1.h"


struct MSG_HEADER{
  int sentinel;
  char msg_type[8];
  unsigned int msg_size;
  unsigned int header_time;
  int end_sentinel;
};

struct MSG_GYRO{
  int sentinel;
  int rotation_x;
  int rotation_y;
  int rotation_z;
  unsigned int last_sample_time;
};

struct MSG_BUTTONS{
  int sentinel;
  unsigned char button_states;
  unsigned int last_press_time;
};

void SendGyroMsg(int rot_x, int rot_y, int rot_z) {
  struct MSG_HEADER gyro_header = {0xABCD, "gyro", 0, 0, 0xDCBA};
  struct MSG_GYRO gyro_message = {0x9876, 0, 0, 0, 0};
                             
  gyro_header.msg_size = sizeof(struct MSG_GYRO);
  gyro_header.header_time = 0x1111; // TCNT;
  
  gyro_message.last_sample_time = TCNT;
  gyro_message.rotation_x = rot_x;
  gyro_message.rotation_y = rot_y;
  gyro_message.rotation_z = rot_z;
  
  SCI1_OutString((char*)&gyro_header, sizeof(struct MSG_HEADER));  
  SCI1_OutString((char*)&gyro_message, sizeof(struct MSG_GYRO));  
}

void SendButtonsMsg() {
  struct MSG_HEADER button_header = {0xABCD, "buttons", 0, 0, 0xDCBA};
  struct MSG_BUTTONS button_message = {0x4321, 0x0A, 0};
                             
  button_header.msg_size = sizeof(struct MSG_BUTTONS);
  button_header.header_time = 0x1111; //TCNT;
  
  button_message.last_press_time = TCNT;
  
  SCI1_OutString((char*)&button_header, sizeof(struct MSG_HEADER));  
  SCI1_OutString((char*)&button_message, sizeof(struct MSG_BUTTONS));   
}


void SendTextMsg(char* text_message) {
  struct MSG_HEADER text_header = {0xABCD, "text", 0, 0, 0xDCBA};
  text_header.msg_size = strlen(text_message);
  text_header.header_time = 0x1111; // TCNT;
  
  SCI1_OutString((char*)&text_header, sizeof(struct MSG_HEADER));  
  SCI1_OutString(text_message, text_header.msg_size);
}




void main(void) {
  /* put your own code here */
  volatile char text_buffer[32];
  int rot_x = 0;
  int rot_y = 10;
  int rot_z = 100;
  
  // initialise the serial
  SCI1_Init(BAUD_9600);
  
  // initialise the timer
  TSCR1_TEN = 1;  
  
  sprintf(text_buffer, "first 12345");
  SendTextMsg(text_buffer);
  SendTextMsg(text_buffer);
  SendTextMsg(text_buffer);
  
  sprintf(text_buffer, "second 123456");
  SendTextMsg(text_buffer);
  SendTextMsg(text_buffer);
  SendTextMsg(text_buffer);
  
	EnableInterrupts;

  SendButtonsMsg();
  SendButtonsMsg();
  SendButtonsMsg();

  for(;;) {
  
    SendGyroMsg(rot_x, rot_y, rot_z);
    
    _FEED_COP(); /* feeds the dog */
  } /* loop forever */
  /* please make sure that you never leave main */
}
