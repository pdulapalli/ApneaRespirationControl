/*
 * File:   SerialSPI.c
 * Author: Praveenanurag Dulapalli
 *
 * Created: 09/26/2015
 * Last Modified: 10/01/2015
 */

#include "SerialSPI.h"
#include "ADXL313.h"
/**
* Function: initializeSPIProtocol
* Operation: Will call the necessary subroutines to initialize the SPI serial protocol with Master = PIC18F46K22
*/



void initializeSPIProtocol(void){
    setUpMasterPIC18(); //
    SPI_CSN = 1; //SPI Chip Select (Inverse) HIGH
    OpenSPI1(SPI_FOSC_4, MODE_11, SMPEND);
    //setUpSlaveADXL313();
}   

void setUpMasterPIC18(void){
    //Set up SSP1 module
    TRISCbits.TRISC3 = OUTPUT; //SCLK
    TRISCbits.TRISC4 = INPUT;  //MISO
    TRISCbits.TRISC5 = OUTPUT; //MOSI
    TRISAbits.TRISA5 = OUTPUT; //Chip Select (Inverse)
    
}

void setUpSlaveADXL313(void){
    initializeADXL313();
}

void writeToADXL313(unsigned char register_address, unsigned char data){
    WriteSPI1(register_address);
}

/*
void enableWrite(void){
    SPI_CSN = 0;
    
}
*/
