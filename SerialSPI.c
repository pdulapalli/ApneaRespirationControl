/*
 * File:   SerialSPI.c
 * Author: Praveenanurag Dulapalli
 *
 * Created: 09/26/2015
 * Last Modified: 09/27/2015
 */

#include "SerialSPI.h"

/**
* Function: initializeSPIProtocol
* Operation: Will call the necessary subroutines to initialize the SPI serial protocol with Master = PIC18F46K22
*/
void initializeSPIProtocol(void){
    TRISC = 0x00; //All of PORTC pins are output
    TRISA = 0x30; //Leave RA4 and RA5 as input
    TRISB = 0x00;

    TRISCbits.TRISC6 = 0;  // RC6/SS - SS Output (Chip Select)
    TRISCbits.TRISC7= 0;   // RC7/SDO - MOSI Output (Serial Data Out)
    TRISBbits.TRISB4= 1;   // RB4/SDI - MISO Input (Serial Data In)
    TRISBbits.TRISB6= 0;   // RB6/SCK - Output (Clock)

    SSPSTAT = 0x40;        // Set SMP=0 and CKE=1. Notes: The lower 6 bit is read only
    SSPCON1 = 0x20;        // Enable SPI Master with Fosc/4
    PORTCbits.RC6 = 1;     // Disable Chip Select
}

void SPI_Write(unsigned char addr,unsigned char data)
{
  // Activate the SS SPI Select pin
  PORTCbits.RC6 = 0;

  // Start MCP23S17 OpCode transmission
  SSPBUF = SPI_SLAVE_ID | ((SPI_SLAVE_ADDR << 1) & 0x0E)| SPI_SLAVE_WRITE;

  // Wait for Data Transmit/Receipt complete
  while(!SSPSTATbits.BF);

  // Start MCP23S17 Register Address transmission
  SSPBUF = addr;

  // Wait for Data Transmit/Receipt complete
  while(!SSPSTATbits.BF);

  // Start Data transmission
  SSPBUF = data;

  // Wait for Data Transmit/Receipt complete
  while(!SSPSTATbits.BF);

  // CS pin is not active
  PORTCbits.RC6 = 1;
}


unsigned char SPI_Read(unsigned char addr)
{
  // Activate the SS SPI Select pin
  PORTCbits.RC6 = 0;

  // Start MCP23S17 OpCode transmission
  //SSPBUF = SPI_SLAVE_ID | ((SPI_SLAVE_ADDR << 1) & 0x0E)| SPI_SLAVE_READ;

  SSPBUF = 0x0E;

  // Wait for Data Transmit/Receipt complete
  while(!SSPSTATbits.BF);

  // Start MCP23S17 Address transmission
  SSPBUF = addr;

  // Wait for Data Transmit/Receipt complete
  while(!SSPSTATbits.BF);

  // Send Dummy transmission for reading the data
  SSPBUF = 0x00;

  // Wait for Data Transmit/Receipt complete
  while(!SSPSTATbits.BF);

  // CS pin is not active
  PORTCbits.RC6 = 1;

  return(SSPBUF);
}