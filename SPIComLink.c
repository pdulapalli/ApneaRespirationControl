#include "SPIComLink.h"
int a;

void Begin_SPI(void){
    TRISAbits.TRISA5 = OUTPUT;
    TRISCbits.TRISC3 = OUTPUT;    //SCK
    TRISCbits.TRISC4 = INPUT;     //MISO
    TRISCbits.TRISC5 = OUTPUT;    //MOSI
    ANSELCbits.ANSC4 = CLEAR;

    /** Start SPI in Mode 1 (polarity), 1 (phase) **/
    
    //CKE (!phase) = 0, SMP = 0 (sample at end of data)
    SSP1STAT = SPI_SMP_END | SPI_CKE_TRANSMIT_FROM_IDLE; 
    
    //SSP1EN = 1, CKP (polarity) = 1  
    SSPCON1 = 0x30; 

    LATAbits.LATA5 = HIGH; //Disable Chip Select

}

void SPI_Write(unsigned char address, unsigned char data){
    unsigned char dummyRead;
    
    // Activate the SS SPI Select pin
    LATAbits.LATA5 = LOW;

    // Start Register Address transmission
    SSPBUF = WRITE_ENABLE | MULTIPLE_BYTE_DISABLE | address;

    // Wait for Data Transmit/Receipt complete
    while(!SSPSTATbits.BF);

    //Read dummy data from SSP Buffer
    dummyRead = SSPBUF;
    
    // Start Data transmission
    SSPBUF = data;

    // Wait for Data Transmit/Receipt complete
    while(!SSPSTATbits.BF);
        
    //Read dummy data from SSP Buffer
    dummyRead = SSPBUF;

    // CS pin is not active
    LATAbits.LATA5 = HIGH;
}

unsigned char SPI_Read(unsigned char address){
    unsigned char readValue, dummyRead;
    
    // Activate the SS SPI Select pin
    LATAbits.LATA5 = LOW;
    
    // Start Address transmission
    SSPBUF = READ_ENABLE | MULTIPLE_BYTE_DISABLE | address;

    // Wait for Data Transmit/Receipt complete
    while(!SSPSTATbits.BF);

    //Read dummy data from SSP Buffer
    dummyRead = SSPBUF;
    
    // Send Dummy transmission for reading the data
    SSPBUF = 0x00;
    
    // Wait for Data Transmit/Receipt complete
    while(!SSPSTATbits.BF){
        dummyRead = SSPBUF;
    }
    
    //Read data input from SSPBUF for MISO signal
    readValue = SSPBUF;
    
    // CS pin is not active
    LATAbits.LATA5 = HIGH;
        
    return(readValue);
}

unsigned char *SPI_Read_Multiple(unsigned char start_address, int numBytesToRead, unsigned char byteData[]){
    unsigned char dummyRead;
    int i; 
    
    // Activate the SS SPI Select pin
    LATAbits.LATA5 = LOW;
    
    /*---Must select first register to read --*/
    
    // Start Address transmission
    SSPBUF = READ_ENABLE | MULTIPLE_BYTE_ENABLE | start_address;

    // Wait for Data Transmit/Receipt complete
    while(!SSPSTATbits.BF);
    

    //Read dummy data from SSP Buffer
    dummyRead = SSPBUF;
    
    for(i = 0; i < numBytesToRead; i++){
        // Send Dummy transmission for reading the data
        SSPBUF = 0x00;
    
        // Wait for Data Transmit/Receipt complete
        while(!SSPSTATbits.BF){
            dummyRead = SSPBUF;
        }
    
        //Read i-th data input from SSPBUF for MISO signal
        byteData[i] = SSPBUF;
    }
        
    // CS pin is not active
    LATAbits.LATA5 = HIGH;
        
    return(byteData);
}

