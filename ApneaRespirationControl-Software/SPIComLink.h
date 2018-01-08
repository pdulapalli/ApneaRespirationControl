 /**
 *  @file SPIComLink.h
 *  @author Praveenanurag Dulapalli
 *  @date 2015-11-26
 *  @brief Provides register information about ADXL313 accelerometer, and
 *  functions to access and make sense of accelerometer measurement data
 *
 *  @copyright Copyright 2015 Praveenanurag Dulapalli
 *  @license
 *  Licensed under the Apache License, Version 2.0 (the "License"); you may not
 *  use this file except in compliance with the License. You may obtain a copy of
 *  the License at <br><br>http://www.apache.org/licenses/LICENSE-2.0<br><br>
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 *  WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
 *  License for the specific language governing permissions and limitations under
 *  the License.}
 */

#ifndef SPICOMLINK_H
#define SPICOMLINK_H

#ifdef  __cplusplus
extern "C" {
#endif

#include "Globals.h"

#include <p18f46k22.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <delays.h>

#include "Lcd.h" // Also includes "General.h" which we need for I/O constants
#include <spi.h>
#include "ADXL313.h"

// SPI Read/Write Parameters
#define MULTIPLE_BYTE_ENABLE 0x40   // 2^7 place bit = 1
#define MULTIPLE_BYTE_DISABLE 0x00  // 2^7 place bit = 0
#define READ_ENABLE 0x80
#define WRITE_ENABLE 0x00
#define DUMMY_DATA  0x00

// SPI Status Parameters
#define SPI_SMP_END                 0x80
#define SPI_SMP_MID                 0x00
#define SPI_CKE_TRANSMIT_TO_IDLE    0x40
#define SPI_CKE_TRANSMIT_FROM_IDLE  0x00

// SPI Control Parameters
#define ENABLE_SSP  0x20 // Enable Synchronous Serial Port
#define SCK_POLARITY_HIGH   0x10 // Idle state for SCK is at a HIGH level
#define SSP_Master_Mode 0x00
#define SCK_FOSC_DIV_4  0x00 // Set SCK at Fosc_rate/4
#define SPI_MODE_11 0x30 // Clock polarity = 1, Clock phase = 1

// MSSP Status Registers
#define SPI_CSN     LATAbits.LATA5
#define SPI_SCK     LATCbits.LATC3
#define SPI_MISO    PORTCbits.RC4
#define SPI_MOSI    LATCbits.LATC5

/**
 * @brief      Configure registers and I/O pins to the SPI 4-wire setting in Mode(1, 1)
 */
void initializeSPI(void);

/**
 * @brief      Write values via SPI to an ADXL313 register (e.g. modify
 *             settings, etc.)
 *
 * @param[in]  address  the 8-bit address of the target ADXL313 register
 * @param[in]  data     the 8-bit value to write to said register
 */
void SPI_Write(unsigned char address, unsigned char data);

/**
 * @brief      Extract values via SPI from an ADXL313 register (e.g. status,
 *             data acquistion)
 *
 * @param[in]  address  the 8-bit address of the target ADXL313 register
 *
 * @return     the 8-bit value read from said register
 */
unsigned char SPI_Read(unsigned char address);

/**
 * @brief      Extract values via SPI from multiple ADXL313 registers (e.g.
 *             status, data acquistion)
 *
 * @param[in]  start_address   the 8-bit address for the first ADXL313
 *                              register in target series
 * @param[in]  numBytesToRead  the number of registers to read consecutively
 * @param      byteData        array to store read bytes in
 *
 * @return     pointer to first element of array containing the bytes read
 */
unsigned char *SPI_Read_Multiple(unsigned char start_address,
                                 int numBytesToRead, unsigned char byteData[]);

#ifdef  __cplusplus
}
#endif

#endif  /* SPICOMLINK_H */

