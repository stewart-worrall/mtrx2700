#include "accelerometer.h"

void convertUnits(AccelRaw *raw_data, AccelScaled *scaled_data){
    scaled_data->x = (float)(raw_data->x)/250;
    scaled_data->y = (float)(raw_data->y)/250;
    scaled_data->z = (float)(raw_data->z)/250;
}
