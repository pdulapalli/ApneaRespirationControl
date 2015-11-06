/*
 * File:   ADXL313.c
 * Author: Praveenanurag Dulapalli
 *
 * Created: 10/02/2015
 * Last Modified: 10/29/2015
 */

#include "ADXL313.h"

void initializeADXL313(void){
    //ADXL313 Register Initialization Sequence

    SPI_Write(REG_ADDR_ADXL313_DATA_FORMAT, ADXL313_SPI_4_WIRE); //Set 4-wire SPI
    Delay10TCYx(1);

    SPI_Write(REG_ADDR_ADXL313_SOFT_RESET, ADXL313_BEGIN_SOFT_RESET); //Reset routine
    Delay10TCYx(1);

    SPI_Write(REG_ADDR_ADXL313_POWER_CTL, ADXL313_STANDBY_MODE); //Standby
    Delay10TCYx(1);

    SPI_Write(REG_ADDR_ADXL313_BW_RATE, ADXL313_DATA_RATE_800_HZ); //Set 800 Hz output data rate
    Delay10TCYx(1);

    SPI_Write(REG_ADDR_ADXL313_INT_ENABLE, ADXL313_DISABLE_ALL_INTERRUPTS); //DISABLE_INTERRUPTS
    Delay10TCYx(1);

    SPI_Write(REG_ADDR_ADXL313_DATA_FORMAT, 0x0A); //Configure data output
    Delay10TCYx(1);

    SPI_Write(REG_ADDR_ADXL313_POWER_CTL, ADXL313_DISABLE_I2C | ADXL313_MEASUREMENT_ENABLE); //Disable sleep-related bits
                                                 //and begin measurement
    Delay10TCYx(1);
}

void readAxisMeasurements(void){
    int i;
    unsigned char buffer[7];
    AccelData currentData;

    SPI_Read_Multiple(REG_ADDR_ADXL313_DATA_X0, 6, buffer);

    currentData.x_axis = concatenateRawValues(buffer[1], buffer[0]);
    currentData.y_axis = concatenateRawValues(buffer[3], buffer[2]);
    currentData.z_axis = concatenateRawValues(buffer[5], buffer[4]);

    addData(&currentData);
}

double computeAmplitude(AccelData *axisMeasurement){
    double x, y, z, amplitude;
    
    x = digitalToAnalogMeasurement(axisMeasurement->x_axis, 2);
    y = digitalToAnalogMeasurement(axisMeasurement->y_axis, 2);
    z = digitalToAnalogMeasurement(axisMeasurement->z_axis, 2);

    amplitude = z - cos(asin(y));

    return amplitude;
}

double digitalToAnalogMeasurement(unsigned int digitalInput, int measurementRange){
    //Range Code:  '0' => 0.5g; '1' => 1.0g; '2' => 2.0g
    //Assumes Full-Resolution Enabled
    //Output unit = milli-G's
    unsigned int magnitude;
    double convertedVal;
    unsigned int sign = (digitalInput >> 11) % 2;

    convertedVal = 0;

    switch(measurementRange){
        case 0:
            magnitude = (digitalInput & 0x01FF);

            if(sign){
                magnitude = ~magnitude + 1;
            }

            magnitude = (magnitude & 0x01FF);

            break;
        case 1:
            magnitude = (digitalInput & 0x03FF);

            if(sign){
                magnitude = ~magnitude + 1;
            }

            magnitude = (magnitude & 0x03FF);

            break;
        case 2:
            magnitude = (digitalInput & 0x07FF);

            if(sign){
                magnitude = ~magnitude + 1;
            }

            magnitude = (magnitude & 0x07FF);

            break;
    }

    convertedVal += magnitude;

    convertedVal *= (double) 1000;
    convertedVal /= (double) 1024;

    convertedVal = sign ? -convertedVal : convertedVal;

    return convertedVal;
}

unsigned int concatenateRawValues(unsigned char upperBits, unsigned char lowerBits){
    unsigned int upperTemp;
    unsigned int concatenatedValue;

    concatenatedValue = (unsigned int) lowerBits;
    upperTemp = (unsigned int) (upperBits);

    concatenatedValue = (upperTemp << 8) | concatenatedValue;

    return concatenatedValue;
}




