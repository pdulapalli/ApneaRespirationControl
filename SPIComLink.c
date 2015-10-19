#include "SPIComLink.h"

void Begin_SPI(void){
    TRISAbits.TRISA5 = OUTPUT;
    TRISCbits.TRISC3 = OUTPUT;    //SCK
    TRISCbits.TRISC4 = INPUT;     //MISO
    TRISCbits.TRISC5 = OUTPUT;    //MOSI

    SSP1STAT = 0x00; //CKE = 0
    SSPCON1 = 0x30; //SSP1EN = 1, CKP = 1

    LATAbits.LATA5 = HIGH; //Disable Chip Select

}

void SPI_Write(unsigned char address, unsigned char data){
    // Activate the SS SPI Select pin
    LATAbits.LATA5 = LOW;

    // Start Register Address transmission
    SSPBUF = WRITE_ENABLE | MULTIPLE_BYTE_DISABLE | address;

    // Wait for Data Transmit/Receipt complete
    while(!SSPSTATbits.BF);

    // Start Data transmission
    SSPBUF = data;

    // Wait for Data Transmit/Receipt complete
    while(!SSPSTATbits.BF);

    // CS pin is not active
    LATAbits.LATA5 = HIGH;
}

unsigned char SPI_Read(unsigned char address, unsigned char multipleByteConfig)
{
    // Activate the SS SPI Select pin
    LATAbits.LATA5 = LOW;

    // Start Address transmission
    SSPBUF = READ_ENABLE | multipleByteConfig | address;

    // Wait for Data Transmit/Receipt complete
    while(!SSPSTATbits.BF);

    // Send Dummy transmission for reading the data
    SSPBUF = 0x00;

    // Wait for Data Transmit/Receipt complete
    while(!SSPSTATbits.BF);

    // CS pin is not active
    LATAbits.LATA5 = HIGH;

    return(SSPBUF);
}


