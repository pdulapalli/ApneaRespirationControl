/*
 * File:   SerialSPI.h
 * Author: Praveenanurag Dulapalli
 *
 * Created: 09/26/2015
 * Last Modified: 09/27/2015
 */

#ifndef SERIALSPI_H
#define	SERIALSPI_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <p18f46k22.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <delays.h>

#include "Lcd.h"

//SPI Slave Device
#define SPI_SLAVE_ID    0x40
#define SPI_SLAVE_ADDR  0x00      // A2=0,A1=0,A0=0
#define SPI_SLAVE_WRITE 0x00
#define SPI_SLAVE_READ  0x01

void initializeSPIProtocol(void); //Setup serial communication between PIC and ADXL313
void SPI_Write(unsigned char addr,unsigned char data); //PIC writes to ADXL313
unsigned char SPI_Read(unsigned char addr); //PIC reads from ADXL313

#ifdef	__cplusplus
}
#endif

#endif	/* SERIALSPI_H */

