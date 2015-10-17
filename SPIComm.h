/* 
 * File:   SPIComm.h
 * Author: pdulapalli
 *
 * Created on October 16, 2015, 10:50 AM
 */

#ifndef SPICOMM_H
#define	SPICOMM_H

#ifdef	__cplusplus
extern "C" {
#endif
  
#include <p18f46k22.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <delays.h>

#include "Lcd.h"
#include <spi.h>
#include "ADXL313.h"
    
#define MULTIPLE_BYTE_ENABLE 0x40   //2^7 place bit = 1
#define MULTIPLE_BYTE_DISABLE 0x00  //2^7 place bit = 0
#define READ_ENABLE 0x80
#define WRITE_ENABLE 0x00
  
void begin_SPI();
void SPI_Write(unsigned char address, unsigned char data);
unsigned char SPI_Read(unsigned char address);

#ifdef	__cplusplus
}
#endif

#endif	/* SPICOMM_H */

