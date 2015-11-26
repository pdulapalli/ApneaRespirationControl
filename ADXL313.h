/*
 * File:   ADXL313.h
 * Author: Praveenanurag Dulapalli
 *
 * Created: 10/02/2015
 * Last Modified: 11/09/2015
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
#include "ApneaMonitor.h"


#ifdef DEFINE_VARIABLES
#define EXTERN /* nothing */
#else
#define EXTERN extern
#endif /* DEFINE_VARIABLES */

/*--------BIT OPERATION CONSTANTS--------*/
#define SIGN_BIT        1
#define ACCEL_MASK      0xFF
#define LSB_PER_G       1024
#define MASK_9_BITS     0x01FF
#define MASK_10_BITS    0x03FF
#define MASK_11_BITS    0x07FF

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


/**
*Function Name: initializeADXL313
*Parameters:    None
*Output:        None
*Purpose:       Write initialization parameters to ADXL313 registers via SPI
**/
void initializeADXL313(void);

/**
*Function Name: readAxisMeasurements
*Parameters:    None
*Output:        AccelData currData: structure with three 16-bit integers corresponding to
                                    acceleration measurements on each axis obtained directly
                                    from ADXL313 registers
*Purpose:       Capture and store acceleration measurements from ADXL313 registers
**/
AccelData readAxisMeasurements(void);

/**
*Function Name: computeAmplitude
*Parameters:    [1] AccelData axisMeasurement: structure with three 16-bit integers corresponding
                                               to acceleration measurements on each axis obtained
                                               directly from ADXL313 registers
                [2] int measurementRange: choose which ADXL313 measurement range in (G's) to use
*Output:        double amplitude: calculated respiration acceleration amplitude
*Purpose:       Calculates respiration acceleration amplitude using the equation
                => A = |z - |cos(arcsin(y))||, where z and y correspond to their respective axes
**/
double computeAmplitude(AccelData axisMeasurement, int measurementRange);

/**
*Function Name: digitalToAnalogMeasurement
*Parameters:    [1] unsigned int digitalInput: sequence of bits corresponding to a digital measurement
                [2] int measurementRange: maximum value of analog measurement
*Output:        double convertedValue: analog value tailored to the measurement range
*Purpose:       Convert a bit sequence into the corresponding analog value
**/
double digitalToAnalogMeasurement(unsigned int digitalInput, int measurementRange);

/**
*Function Name: concatenateRawValues
*Parameters:    [1] unsigned char upperBits: contains bits 15-8 of a 16-bit number
                [2] unsigned char lowerBits: contains bits 7-0 of a 16-bit number
*Output:        unsigned int concatenatedValue: 16-bit integer with the upper 8 and lower
                                                8 bits concatenated
*Purpose:       Combine a value split across two 8-bit variables into a single 16-bit variable
**/
unsigned int concatenateRawValues(unsigned char upperBits, unsigned char lowerBits);

/**
*Function Name: measurementGracePeriod
*Parameters:    [1] int numSeconds: how long to execute function
                [2] int measurementRange: maximum value of analog measurement
*Output:        None
*Purpose:       Capture series of measurements to fill up data buffer and flush outdated values,
                without performing apnea check. Needed to avoid sequential stimulation.
**/
void measurementGracePeriod(int numSeconds, int measurementRange);

#ifdef	__cplusplus
}
#endif

#endif	/* ADXL313_H */

