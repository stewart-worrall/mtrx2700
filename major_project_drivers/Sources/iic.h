#ifndef IIC_HEADER
#define IIC_HEADER

typedef unsigned char uint8_t;
typedef unsigned int uint16_t;


typedef enum {
  IIC_20KHZ,
  IIC_100KHZ 
} IIC_SPEED;

// initialise the I2C interface
//  speed parameter to be selected from the options in IIC_SPEED
void iicinit(IIC_SPEED iic_speed);


typedef enum {
  NO_ERROR = 0, 
  NO_RESPONSE, 
  NAK_RESPONSE, 
  IIB_CLEAR_TIMEOUT, 
  IIB_SET_TIMEOUT,
  RECEIVE_TIMEOUT,
  IIC_DATA_SIZE_TOO_SMALL 
} IIC_ERRORS;


// requests that a device provides data to the bus
// NOTE: this should be followed by an iic_read_data function call.
IIC_ERRORS iic_request_data(uint8_t device, uint8_t address);


// This function reads sets of uint16_t values and puts them in the buffer
//   they are rearranged as the i2c sensors used read the LSB first
IIC_ERRORS iic_read_data(uint8_t device, uint8_t *buffer, uint8_t buffer_size);


IIC_ERRORS iic_send_data(uint8_t device, uint8_t *buffer, uint8_t buffer_size);


// interrupt used for calculating the iic timeout
__interrupt void TC7_ISR(void);
void Init_TC7 (void);


#endif