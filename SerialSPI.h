/*
 * File:   SerialSPI.h
 * Author: Praveenanurag Dulapalli
 *
 * Created: 09/26/2015
 * Last Modified: 10/01/2015
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
#include <spi.h>
#include "ADXL313.h"

    
//SPI Parameters (SPI Module 1)
#define SPI_MASTER_CLOCK SPI_FOSC_4 //Divide internal clock speed by 16
#define SPI_BUS_MODE MODE_11 //Set clock polarity and clock phase; clock idle state is 1
                             //Mode 1,1--Empirically, data bits synchronized to
                             //rising edge of clock, clock itself pulled HIGH switches LOW as it oscillates
#define SPI_DATA_SAMPLE_PHASE SMPEND
    
#define SPI_CLK LATCbits.LATC3
#define SPI_MISO PORTCbits.RC4
#define SPI_MOSI LATCbits.LATC5
#define SPI_CSN LATAbits.LATA5

void initializeSPIProtocol(void); //Setup serial communication between PIC and ADXL313
void setUpMasterPIC18(void);
void setUpSlaveADXL313(void);
void writeToADXL313(unsigned char register_address, unsigned char data);

#ifdef	__cplusplus
}
#endif

#endif	/* SERIALSPI_H */

