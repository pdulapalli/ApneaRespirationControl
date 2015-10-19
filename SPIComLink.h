/*
 * File:   SPIComLink.h
 * Author: pdulapalli
 *
 * 
 */

#ifndef SPICOMLINK_H
#define SPICOMLINK_H

#ifdef  __cplusplus
extern "C" {
#endif

#include <p18f46k22.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <delays.h>

#include "Lcd.h" //Also includes "General.h" which we need for I/O constants
#include <spi.h>
#include "ADXL313.h"

#define MULTIPLE_BYTE_ENABLE 0x40   //2^7 place bit = 1
#define MULTIPLE_BYTE_DISABLE 0x00  //2^7 place bit = 0
#define READ_ENABLE 0x80
#define WRITE_ENABLE 0x00


//SPI Status Parameters
#define SPI_SMP_END                 0x80
#define SPI_SMP_MID                 0x00
#define SPI_CKE_TRANSMIT_FALLING
#define SPI_CKE_TRANSMIT_RISING

//SPI Control Parameters
#define ENABLE_SSP  0x20    //Enable Synchronous Serial Port
#define SCK_POLARITY_HIGH   0x10 //Idle state for SCK is at a HIGH level
#define SSP_Master_Mode 0x00
#define SCK_FOSC_DIV_4  0x00    //Set SCK at Fosc_rate/4

void Begin_SPI(void);
void SPI_Write(unsigned char address, unsigned char data);

unsigned char SPI_Read(unsigned char address, unsigned char multipleByteConfig);

#ifdef  __cplusplus
}
#endif

#endif  /* SPICOMLINK_H */

