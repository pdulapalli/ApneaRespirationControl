/*
 * File:   ADXL313.h
 * Author: Praveenanurag Dulapalli
 *
 * Created on October 2, 2015, 11:03 AM
 */

#ifndef ADXL313_H
#define	ADXL313_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <p18f46k22.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <delays.h>

#ifdef DEFINE_VARIABLES
#define EXTERN /* nothing */
#else
#define EXTERN extern
#endif /* DEFINE_VARIABLES */

/*-------------------- BEGIN REGISTER ADDRESSES ----------------*/

//Device ID Registers
#define ADXL313_DEVID_0         0x00
#define ADXL313_DEVID_1         0x01
#define ADXL313_PARTID          0x02
#define ADXL313_REVID           0x03
#define ADXL313_XID             0x04

//Device Reset Register
#define ADXL313_SOFT_RESET      0x18

//Offset Registers
#define ADLX313_OFSX            0x1E
#define ADXL313_OFSY            0x1F
#define ADXL313_OFSZ            0x20

//Threshold Registers
#define ADXL313_THRESH_ACT      0x24
#define ADXL313_TIME_INACT      0x26
#define ADXL313_ACT_INACT_CTL   0x27

#define ADXL313_BW_RATE         0x2C
#define ADXL313_POWER_CTL       0x2D
#define ADXL313_INT_ENABLE      0x2E
#define ADXL313_INT_MAP         0x2F
#define ADXL313_INT_SOURCE      0x30

//Data Output Registers
#define ADXL313_DATA_FORMAT     0x31
#define ADXL313_DATA_X0         0x32
#define ADXL313_DATA_X1         0x33
#define ADXL313_DATA_Y0         0x34
#define ADXL313_DATA_Y1         0x35
#define ADXL313_DATA_Z0         0x36
#define ADXL313_DATA_Z1         0x37

//FIFO Registers
#define ADXL313_FIFO_CTL        0x38
#define ADXL313_FIFO_STATUS     0x39
    

/*-------------------- Control Bits and Parameters ----------------*/
    
//Enable Reset
#define ADXL313_BEGIN_SOFT_RESET    0x52
    
//Custom Parameters for Power Control
#define ADXL313_NO_SLEEP            0b0
#define ADXL313_DEASSERT_LINK       0b0
#define ADXL313_DISABLE_I2C         0b1
#define ADXL313_MEASUREMENT_MODE    0b1

//Custom Parameters for Measurement
#define ADXL313_SPI_4_WIRE          0b0
#define ADXL313_SELF_TEST_OFF       0b0
#define ADXL313_HALF_G_RANGE        0b00
#define ADXL313_LEFT_JUSTIFY        0b1

EXTERN volatile unsigned char SOFTRESET;
    
EXTERN volatile unsigned char DATAFORMAT;
EXTERN volatile struct {
    unsigned RANGE:2;
    unsigned JUSTIFY:1;
    unsigned FULL_RES:1;
    unsigned :1;
    unsigned INT_INVERT:1;
    unsigned SPI:1;
    unsigned SELF_TEST:1;
} DATAFORMATbits;

EXTERN volatile unsigned char POWERCTL;
EXTERN struct {
    unsigned WAKE_UP:2;
    unsigned SLEEP:1;
    unsigned MEASURE:1;
    unsigned AUTO_SLEEP:1;
    unsigned LINK:1;
    unsigned I2C_DISABLE:1;
    unsigned :1;
} POWERCTLbits;

/*-------BIT SHIFT CONSTANTS------*/
#define D7 7
#define D6 6
#define D5 5
#define D4 4
#define D3 3
#define D2 2
#define D1 1
#define D0 0

#define HIGH_BIT 0b1
#define LOW_BIT 0b0

void initializeADXL313(void);
void updateRegisterControlBits(unsigned char whichRegister);
void prepareRegisterControlBits(unsigned char whichRegister);

#ifdef	__cplusplus
}
#endif

#endif	/* ADXL313_H */

