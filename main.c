/*
 * File:   main.c
 * Author: Praveenanurag Dulapalli
 *
 * Created: 09/26/2015
 * Last Modified: 10/01/2015
 */

/*
Rule of thumb: Always read inputs from PORTx and write outputs to LATx. 
               If you need to read what you set an output to, read LATx. 
 */

#include <p18f46k22.h>
#include <stdio.h>
#include <stdlib.h>
#include <delays.h>
#include <spi.h>
#include <string.h>

#include "Lcd.h"
#include "SPIComm.h" //Handle SPI Serial communication between PIC Master and ADXL313 Slave
#include "DataManager.h" //Manage access, updating, and organization of data via circular buffer
#include "ApneaMonitor.h" //Amplitude detection to alert if user in apnea condition

#pragma config FOSC = INTIO7   // Internal OSC block, Port Function on RA6/7
#pragma config WDTEN = OFF      // Watch Dog Timer disabled. SWDTEN no effect
#pragma config XINST = OFF

//#define nop() _asm nop _endasm
//#define NOP_PER_MS 182

int current_state; //Tracking variable to manage what state device currently in

//void delay_ms(int milliseconds);

void main() {
    char stringOut[8];
    int i;
    unsigned char temp;
    unsigned char dataIn;

    //Set up 16 MHz internal oscillator
    //Note: 1 TCY = 295 ns, 1 ms approx. = 3390 TCY => 3 KTCY
    //Note: Empirically see that 4050 TCY => 1 msx
    OSCCONbits.IDLEN = 0;
    OSCCONbits.IRCF = 100; //111(16 MHz); 100(2 MHz)
    OSCCONbits.OSTS = 0; 
    OSCCONbits.HFIOFS = 1; 
    OSCCONbits.SCS = 10;
    
    //Set up LCD
    
    ANSELD = 0x00;
    TRISD = 0x00; //Digital out
    
    LCDInit();
    LCDClear();
    LCDGoto(0, 0);
     
    
    
    begin_SPI();
    
    SPI_Write(REG_ADXL313_SOFT_RESET, ADXL313_BEGIN_SOFT_RESET); //Reset routine
        Delay10TCYx(1);
    
    SPI_Write(REG_ADXL313_POWER_CTL, (ADXL313_MEASUREMENT_ENABLE << 3)); //Standby
        Delay10TCYx(1);
    
        
    SPI_Write(REG_ADXL313_BW_RATE, 0b00001110); //Set 1600 Hz output data rate
        Delay10TCYx(1);
    
    SPI_Write(REG_ADXL313_INT_ENABLE, 0x00);
        Delay10TCYx(1);
        
    SPI_Write(REG_ADXL313_DATA_FORMAT, 0b00001000); //Configure data output
        Delay10TCYx(1);
        
             //WORKS UPTO HERE 
    SPI_Write(REG_ADXL313_POWER_CTL, 0b01001000); //Disable sleep-related bits
                                                   //Begin measurement
        Delay10TCYx(1);
    
    
    while(1){
        dataIn = SPI_Read(0x32);
        
        LCDGoto(0, 0);
         
        Delay10KTCYx(1);
    }
     
    
    
    /*
    while(1){
        dataIn = readFromADXL313(ADXL313_DATA_X0);
        //dataIn = 0b10010101;
        delay_ms(10);
        LCDGoto(0, 0);
        for(i = 7; i >= 0; i--){
            temp = (dataIn >> i) % 2;
            if(temp == 1){
                temp = '1';
            } else if(temp == 0){
                temp = '0';
            }
            LCDPutChar(temp);
        }
    }
    */
    
    

    
    /**
    *CODE OUTLINE:
    *   [1] Idle until user activates system
    *   [2] Establish SPI serial connection between PIC18F46K22 (Master) and ADXL313 (Slave)
    *   [3] Initialize circular buffer and collect data until buffer is fully loaded
    *   [4] Extract x, y, z, components of data and compute amount of displacement
    *           *For first full set of samples, compute the mean
        [5] Continue to collect data into buffer and repeating step [4] as necessary
    *   [6] If amplitude falls below certain percentage threshold (of mean), set stimulus I/O Pin HIGH
    */
}


