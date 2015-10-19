/*
 * File:   main.c
 * Author: Praveenanurag Dulapalli
 *
 * Created: 09/26/2015
 * Last Modified: 10/19/2015
 */

/*
Rule of thumb: Always read inputs from PORTx and write outputs to LATx.
               If you need to read what an outputs are set to, read LATx.
 */

#include <p18f46k22.h>
#include <stdio.h>
#include <stdlib.h>
#include <delays.h>
#include <string.h>

#include "Lcd.h"            //Utilize LCD Display if needed
#include "SPIComLink.h"     //Handle SPI Serial communication between PIC Master and ADXL313 Slave
#include "DataManager.h"    //Manage access, updating, and organization of data via circular buffer
#include "ApneaMonitor.h"   //Amplitude detection to alert if user in apnea condition
#include "ADXL313.h"        //ADLX313 register definitions and bit configurations

#pragma config FOSC = INTIO7   // Internal OSC block, Port Function on RA6/7
#pragma config WDTEN = OFF     // Watch Dog Timer disabled
#pragma config XINST = OFF     // Disable extended instruction set

#define nop() _asm nop _endasm
#define NOP_PER_MS 182

//int current_state; //Tracking variable to manage what state device currently in

int wer;

unsigned char DataFormatReg_ADXL313, PowerCTLReg_ADXL313,
                     IntEnableReg_ADXL313, BWRateReg_ADXL313,
                     SoftResetReg_ADXL313;

PowerCTLReg_ADXL313_Bitfield PowerCTLReg_ADXL313_bits;
PowerCTLReg_ADXL313_Bitfield PCTLR_Empty = {0};

DataFormatReg_ADXL313_Bitfield DataFormatReg_ADXL313_bits;
DataFormatReg_ADXL313_Bitfield DFR_Empty = {0};

IntEnableReg_ADXL313_Bitfield IntEnableReg_ADXL313_bits;
IntEnableReg_ADXL313_Bitfield IER_Empty = {0};

BWRateReg_ADXL313_Bitfield BWRateReg_ADXL313_bits;
BWRateReg_ADXL313_Bitfield BWRR_Empty = {0};

void defineGlobalVariables(void){
    DataFormatReg_ADXL313 = 0x00;
    DataFormatReg_ADXL313_bits = DFR_Empty;
    
    PowerCTLReg_ADXL313 = 0x00;
    PowerCTLReg_ADXL313_bits = PCTLR_Empty;

    IntEnableReg_ADXL313 = 0x00;
    IntEnableReg_ADXL313_bits = IER_Empty;

    BWRateReg_ADXL313 = 0x00;
    BWRateReg_ADXL313_bits = BWRR_Empty;

    SoftResetReg_ADXL313 = 0x00;            
}

void main() {
    int i;
    unsigned char dataIn;

    defineGlobalVariables();
   
    //Set up 16 MHz internal oscillator
    //Note: 1 TCY = 295 ns, 1 ms approx. = 3390 TCY => 3 KTCY
    //Note: Empirically see that 4050 TCY => 1 ms
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

    Begin_SPI();
    
    initializeADXL313();
    
    while(1){
        dataIn = SPI_Read(REG_ADDR_ADXL313_DEVID_0, MULTIPLE_BYTE_DISABLE);
        Delay10KTCYx(1);
    }

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


