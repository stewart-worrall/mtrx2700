#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */

// need this for string functions
#include <stdio.h>

#include "pll.h"
#include "simple_serial.h"
#include "l3g4200d.h"



void main(void) {

  AccelRaw read_accel;
  AccelScaled scaled_accel;

  GyroRaw read_gyro;
  
  MagRaw read_magnet;
  
  int error_code = NO_ERROR;
  unsigned char buffer[128];

  #ifndef SIMULATION_TESTING

  // make sure the board is set to 24MHz
  PLL_Init();

  #endif


  // initialise the simple serial
  SCI1_Init(BAUD_9600);
  
  #ifndef SIMULATION_TESTING
  
  // initialise the sensor suite
  error_code = iicSensorInit();
  
  // write the result of the sensor initialisation to the serial
  if (error_code == NO_ERROR) {
    sprintf(buffer, "NO_ERROR");
    SCI1_OutString(buffer);
  } else {
    sprintf(buffer, "ERROR %d");
    SCI1_OutString(buffer);    
  }
  
  #else
  
  Init_TC7();
  
  #endif
  
  
  
    
	EnableInterrupts;
  COPCTL = 7;

  for(;;) {
  
    #ifndef SIMULATION_TESTING
  
    // read the raw values
    getRawDataGyro(&read_gyro);
    getRawDataAccel(&read_accel);
    getRawDataMagnet(&read_magnet);
    
    #else
    
    // inject some values for simulation
    read_gyro.x = 123; read_gyro.y = 313; read_gyro.z = 1002;
    read_accel.x = 124; read_accel.y = 312; read_accel.z = 2002;
    read_magnet.x = 125; read_magnet.y = 311; read_magnet.z = 3002;
    
    #endif

    // convert the acceleration to a scaled value
    convertUnits(&read_accel, &scaled_accel);    
    
    // format the string of the sensor data to go the the serial
    sprintf(buffer, "%.2f, %.2f, %.2f, %d, %d, %d, %d, %d, %d \r\n", scaled_accel.x, scaled_accel.y, scaled_accel.z, read_gyro.x, read_gyro.y, read_gyro.z, read_magnet.x, read_magnet.y, read_magnet.z);
    
    // output the data to serial
    SCI1_OutString(buffer);
    
    _FEED_COP(); /* feeds the dog */
  } /* loop forever */
  
  /* please make sure that you never leave main */
}
