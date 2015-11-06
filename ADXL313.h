/*
 * File:   ADXL313.h
 * Author: Praveenanurag Dulapalli
 *
 * Created: 10/02/2015
 * Last Modified: 10/29/2015
 */

#ifndef ADXL313_H
#define	ADXL313_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "Globals.h"
    
#include <p18f46k22.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <delays.h>
    
#include "Lcd.h" //Also includes "General.h" which we need for I/O constants
#include "DataManager.h"
#include "SPIComLink.h"


#ifdef DEFINE_VARIABLES
#define EXTERN /* nothing */
#else
#define EXTERN extern
#endif /* DEFINE_VARIABLES */

#define SIGN_BIT    1
#define ACCEL_MASK  0xFF

/*-------------------- BEGIN REGISTER ADDRESSES ----------------*/

//Device ID Registers
#define REG_ADDR_ADXL313_DEVID_0         0x00
#define REG_ADDR_ADXL313_DEVID_1         0x01
#define REG_ADDR_ADXL313_PARTID          0x02
#define REG_ADDR_ADXL313_REVID           0x03
#define REG_ADDR_ADXL313_XID             0x04

//Device Reset Register
#define REG_ADDR_ADXL313_SOFT_RESET      0x18

//Offset Registers
#define REG_ADDR_ADXL313_OFSX           0x1E
#define REG_ADDR_ADXL313_OFSY           0x1F
#define REG_ADDR_ADXL313_OFSZ           0x20

//Threshold Registers
#define REG_ADDR_ADXL313_THRESH_ACT      0x24
#define REG_ADDR_ADXL313_TIME_INACT      0x26
#define REG_ADDR_ADXL313_ACT_INACT_CTL   0x27

#define REG_ADDR_ADXL313_BW_RATE         0x2C
#define REG_ADDR_ADXL313_POWER_CTL       0x2D
#define REG_ADDR_ADXL313_INT_ENABLE      0x2E
#define REG_ADDR_ADXL313_INT_MAP         0x2F
#define REG_ADDR_ADXL313_INT_SOURCE      0x30

//Data Output Registers
#define REG_ADDR_ADXL313_DATA_FORMAT     0x31
#define REG_ADDR_ADXL313_DATA_X0         0x32
#define REG_ADDR_ADXL313_DATA_X1         0x33
#define REG_ADDR_ADXL313_DATA_Y0         0x34
#define REG_ADDR_ADXL313_DATA_Y1         0x35
#define REG_ADDR_ADXL313_DATA_Z0         0x36
#define REG_ADDR_ADXL313_DATA_Z1         0x37

//FIFO Registers
#define REG_ADDR_ADXL313_FIFO_CTL        0x38
#define REG_ADDR_ADXL313_FIFO_STATUS     0x39


/*-------------------- Control Bits and Parameters ----------------*/

//Enable Reset
#define ADXL313_BEGIN_SOFT_RESET    0x52

//Parameters for Power Control
#define ADXL313_DISABLE_I2C         0x40
#define ADXL313_DEASSERT_LINK       0x00
#define ADXL313_DISABLE_AUTO_SLEEP  0x00
#define ADXL313_MEASUREMENT_ENABLE  0x08
#define ADXL313_STANDBY_MODE        0x00
#define ADXL313_NO_SLEEP            0x00

//Parameters for Data Format
#define ADXL313_SELF_TEST_OFF       0x00
#define ADXL313_SPI_4_WIRE          0x00
#define ADXL313_USE_FULL_RES        0x08
#define ADXL313_10_BIT_RES          0x00
#define ADXL313_RIGHT_JUSTIFY       0x00
#define ADXL313_HALF_G_RANGE        0x00
#define ADXL313_ONE_G_RANGE         0x01
#define ADXL313_TWO_G_RANGE         0x02

//Interrupt Management
#define ADXL313_DISABLE_ALL_INTERRUPTS      0x00

//Bandwidths and Rate Parameters
#define ADXL313_DATA_RATE_1600_HZ           0x0E
#define ADXL313_DATA_RATE_800_HZ            0x0D


void initializeADXL313(void);
void writeRegisterControlBits(unsigned char regAddr, unsigned char regControlBits);
void updateRegisterControlBits(unsigned char regAddr);
void readAxisMeasurements(void);
double digitalToAnalogMeasurement(unsigned int digitalInput, int measurementRange);
unsigned int concatenateRawValues(unsigned char upperBits, unsigned char lowerBits);
double computeAmplitude(AccelData *axisMeasurement); //Perform calculation to obtain amplitude of displacement


#ifdef	__cplusplus
}
#endif

#endif	/* ADXL313_H */

