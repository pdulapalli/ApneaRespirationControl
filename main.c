/*
 * File:   main.c
 * Author: Praveenanurag Dulapalli
 *
 * Created: 09/26/2015
 * Last Modified: 10/01/2015
 */

/*
Rule of thumb: Always read inputs from PORTx and write outputs to LATx. If you need to read what you set an output to, read LATx. 
 */

#include <p18f46k22.h>
#include <stdio.h>
#include <stdlib.h>
#include <delays.h>
#include <spi.h>
#include "Lcd.h"

#include "SerialSPI.h" //Handle SPI Serial communication between PIC Master and ADXL313 Slave
#include "DataManager.h" //Manage access, updating, and organization of data via circular buffer
#include "ApneaMonitor.h" //Amplitude detection to alert if user in apnea condition

#pragma config FOSC = INTIO7   // Internal OSC block, Port Function on RA6/7
#pragma config WDTEN = OFF      // Watch Dog Timer disabled. SWDTEN no effect

 #define nop() _asm nop _endasm

int current_state; //Tracking variable to manage what state device currently in

void main() {
    //Set up 16 MHz internal oscillator
    
    OSCCONbits.IDLEN = 0;
    OSCCONbits.IRCF = 111; //111(16 MHz); 100(2 MHz)
    OSCCONbits.OSTS = 0; 
    OSCCONbits.HFIOFS = 1; 
    OSCCONbits.SCS = 10;
    
    initializeSPIProtocol();
    
    SPI_CLK = DISABLE;
    
    nop();
    
    while(1){
        SPI_CSN = 0;
        WriteSPI1(0xF0);
        SPI_CSN = 1;
    }
    //Set up LCD
    //ANSELD = 0x00;
    //TRISD = 0x00; //Digital out
    
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


