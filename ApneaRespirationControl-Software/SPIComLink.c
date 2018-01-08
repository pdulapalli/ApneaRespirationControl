 /**
 *  @file SPIComLink.c
 *  @author Praveenanurag Dulapalli
 *  @date 2015-11-26
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

#include "SPIComLink.h"

void initializeSPI(void) {
    TRISAbits.TRISA5 = OUTPUT;    //CSN  (CHIP SELECT)
    TRISCbits.TRISC3 = OUTPUT;    //SCK  (CLOCK)
    TRISCbits.TRISC4 = INPUT;     //MISO (ADXL SDO)
    TRISCbits.TRISC5 = OUTPUT;    //MOSI (ADXL SDI)
    ANSELCbits.ANSC4 = CLEAR;     //Ensure Pin RC4 accepts digital inputs

    /** Start SPI in Mode 1 (polarity), 1 (phase) **/

    // CKE (!phase) = 0, SMP = 0 (sample at end of data)
    SSP1STAT = SPI_SMP_END | SPI_CKE_TRANSMIT_FROM_IDLE;

    // SSP1EN = 1, CKP (polarity) = 1
    SSPCON1 = SPI_MODE_11;
    LATAbits.LATA5 = HIGH; //Disable Chip Select
}

void SPI_Write(unsigned char address, unsigned char data) {
    unsigned char dummyRead; //Vessel used to clear SPI buffer

    //Activate Chip Select
    LATAbits.LATA5 = LOW;

    // Start Register Address transmission
    SSPBUF = WRITE_ENABLE | MULTIPLE_BYTE_DISABLE | address;

    // Wait for Data Transmit/Receipt complete
    while (!SSPSTATbits.BF);

    //Read dummy data from SSP Buffer
    dummyRead = SSPBUF;

    // Start Data transmission
    SSPBUF = data;

    // Wait for Data Transmit/Receipt complete
    while (!SSPSTATbits.BF);

    //Read dummy data from SSP Buffer
    dummyRead = SSPBUF;

    //Deactivate Chip Select
    LATAbits.LATA5 = HIGH;
}

unsigned char SPI_Read(unsigned char address) {
    unsigned char readValue, dummyRead;

    //Activate Chip Select
    LATAbits.LATA5 = LOW;

    // Start Address transmission
    SSPBUF = READ_ENABLE | MULTIPLE_BYTE_DISABLE | address;

    // Wait for Data Transmit/Receipt complete
    while(!SSPSTATbits.BF);

    //Read dummy data from SSP Buffer
    dummyRead = SSPBUF;

    // Send Dummy transmission for reading the data
    SSPBUF = DUMMY_DATA;

    // Wait for Data Transmission/Reception to complete
    while(!SSPSTATbits.BF){
        dummyRead = SSPBUF;
    }

    //Read data input from SSPBUF for MISO signal
    readValue = SSPBUF;

    //Deactivate Chip Select
    LATAbits.LATA5 = HIGH;
    return readValue;
}

unsigned char *SPI_Read_Multiple(unsigned char start_address,
                                 int numBytesToRead,
                                 unsigned char byteData[]) {
    unsigned char dummyRead;
    unsigned char *readValues;
    int i;

    //Activate Chip Select
    LATAbits.LATA5 = LOW;

    /*---Must select first register to read --*/

    // Start Address transmission
    SSPBUF = READ_ENABLE | MULTIPLE_BYTE_ENABLE | start_address;

    // Wait for Data Transmission/Reception to complete
    while (!SSPSTATbits.BF);

    //Read dummy data from SSP Buffer
    dummyRead = SSPBUF;

    // Keep sending series of clock pulses until all necessary bytes are read
    for (i = 0; i < numBytesToRead; i++) {
        // Note: approximate delay between each pair of transmissions = 118 us

        // Send Dummy transmission for reading the data
        SSPBUF = DUMMY_DATA;

        // Wait for Data Transmit/Receipt complete
        while (!SSPSTATbits.BF) {
            dummyRead = SSPBUF;
        }

        // Read i-th data input from SSPBUF for MISO signal
        byteData[i] = SSPBUF;
    }

    // Deactivate Chip Select
    LATAbits.LATA5 = HIGH;
    readValues = &byteData[0];
    return readValues;
}

