#ifndef L3G4200D_HEADER
#define L3G4200D_HEADER

// file l3g4200d.h
//   public interface for the l3g4200d sensor suite
//   this interface allows you to initalise the sensors
//   and read the raw data values
//   
//   these values require further scaling according to the 
//   datasheets

#include "iic.h"
#include "accelerometer.h"

// data structures containing the raw values

typedef struct GyroRaw {
  int x;
  int y;
  int z;
} GyroRaw;

typedef struct MagRaw {
  int x;
  int y;
  int z;
} MagRaw;


// Initialise each sensor
IIC_ERRORS iicSensorInit();

// Get the raw acceleration data from the sensor
IIC_ERRORS getRawDataAccel(AccelRaw *raw_data);


// Get the raw magnetic data from the sensor
IIC_ERRORS getRawDataMagnet(MagRaw *raw_data);


// Get the raw gyro data from the sensor
IIC_ERRORS getRawDataGyro(GyroRaw *raw_data);

#endif