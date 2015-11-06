/*
 * File:   main.c
 * Author: Praveenanurag Dulapalli
 *
 * Created: 09/26/2015
 * Last Modified: 10/30/2015
 */

#include "Globals.h"

#include <p18f46k22.h>
#include <stdio.h>
#include <stdlib.h>
#include <delays.h>
#include <string.h>

#include "Lcd.h"            //Utilize LCD Display if needed
#include "SPIComLink.h"     //Handle SPI Serial communication between PIC Master and ADXL313 Slave
#include "DataManager.h"    //Manage access, updating, and organization of data via circular buffer
#include "ApneaMonitor.h"   //Amplitude detection to alert if user in apnea condition
#include "ADXL313.h"        //ADLX313 functions, register definitions, and bit configurations

#pragma config FOSC = INTIO7   // Internal OSC block, Port Function on RA6/7
#pragma config WDTEN = OFF     // Watch Dog Timer disabled
#pragma config XINST = OFF     // Disable extended instruction set (increase stack frame)

/*-----STATE MACHINE CONDITIONS-----*/

#define STATE_IDLE                  0x0
#define STATE_INITIALIZE            0x1
#define STATE_MEASURE               0x2
#define STATE_CALCULATE             0x3
#define STATE_APNEA_DETECTION       0x4
#define STATE_TEST_THRESHOLD        0x5

unsigned int current_state; //Tracking variable to manage what state device currently in
unsigned int button_press;

void initializeSystems(void);
void measureAndDisplay(void);
void testBuffer(void);
void testRespiration(void);
void LCDOutputString(unsigned char output_buffer[]);
void printDouble(double myDouble, int decimalPlaces);

void initializePIC(void){
    //Set up 16 MHz internal oscillator
    //  Note: 1 TCY = 295 ns, 1 ms approx. = 3390 TCY => 3 KTCY
    //  Note: Empirically see that 4050 TCY => 1 ms
    OSCCONbits.IDLEN = 0;
    OSCCONbits.IRCF = 110; //111(16 MHz); 110(8 MHz); 100(2 MHz)
    OSCCONbits.OSTS = 0;
    OSCCONbits.HFIOFS = 1;
    OSCCONbits.SCS = 10;

    //Set up LCD
    ANSELD = 0x00;
    TRISD = 0x00; //Digital out

    LCDInit();
    LCDClear();
}

    /**
    *CODE OUTLINE:
    *   [1] Idle until user activates system
    *   [2] Establish SPI serial connection between PIC18F46K22 (Master) and ADXL313 (Slave)
    *   [3] Initialize circular buffer and collect data until buffer is fully loaded
    *   [4] Extract x, y, z, components of data and compute amount of acceleration
    *           *For first full set of samples, compute the mean
        [5] Continue to collect data into buffer and repeating step [4] as necessary
    *   [6] If amplitude falls below certain percentage threshold (of mean), set stimulus I/O Pin HIGH
    */

void main() {
    unsigned char x1, x0;
    unsigned int x10, i; //Index counter
    //double s_p;
    double dub = 3.14159;
    i = 0;
    
    TRISEbits.TRISE1 = OUTPUT;
    
    current_state = STATE_INITIALIZE;

    while(1){
        switch(current_state){
            case STATE_IDLE:
                delay_ms(1);
                break;
            case STATE_INITIALIZE:
                initializeSystems();
                current_state = STATE_MEASURE;
                break;
            case STATE_MEASURE:
                while(current_state == STATE_MEASURE){
                    measureAndDisplay();
                    delay_ms(1);
                }
                break;
            case STATE_CALCULATE:
                break;
            case STATE_APNEA_DETECTION:
                break;
            case STATE_TEST_THRESHOLD:
                while(current_state = STATE_TEST_THRESHOLD){
                    testRespiration();
                    Delay10KTCYx(0);
                }
                break;
            default:
                break;
        }
    }
}

void printDouble(double myDouble, int decimalPlaces){
    unsigned char buffer[31];
    long int_a, frac_a; // our integer and fractional temps
    int_a = myDouble; // standard C cast
    frac_a = (myDouble - int_a)*pow(10, (double) decimalPlaces); // expose up to 9 decimals
    frac_a = (frac_a < 0) ? -frac_a : frac_a; // if negative, change sign
    sprintf(buffer, "%ld.%ld", int_a, frac_a); // get the ascii
    LCDOutputString(buffer);
}

void initializeSystems(void){
    initializePIC();
    initializeSPI();
    initializeADXL313();
}

void measureAndDisplay(void){
    AccelData test;
    unsigned int i, q, debugger;
    unsigned char dataBuffer[31];
    unsigned char currentEntry;
    unsigned char LCD_string_buffer[31]; //General purpose LCD output buffer
    double analogValue;

    SPI_Read_Multiple(REG_ADDR_ADXL313_DATA_X0, 6, dataBuffer);
    
    /*
    LCDGoto(0, 0);

    for(i = 0; i < 6; i++){
        
        currentEntry = dataBuffer[i];
        
        if(i % 3 == 0){
            LCDGoto(0, (i % 2));
        }

        sprintf(LCD_string_buffer, "0x%02X \0", currentEntry);
        LCDOutputString(LCD_string_buffer);

    }
    */
    
    q = concatenateRawValues(dataBuffer[5], dataBuffer[4]);

    LCDGoto(0, 0);
    sprintf(LCD_string_buffer, "0x%04X \0", q);
    LCDOutputString(LCD_string_buffer);
      
    
    LCDGoto(0, 1);
    analogValue = digitalToAnalogMeasurement(q, 2);
    printDouble(analogValue, 1);

    Delay10TCYx(0);      
}

void testBuffer(void){
    unsigned int i, deBogue;
    AccelData currData;
    
    for(i = 0; i < 2*BUFFER_LENGTH; i++){
        currData.x_axis = 3*i;
        currData.y_axis = 3*i+1;
        currData.z_axis = 3*i+2;
        deBogue = 1;
        addData(&currData);
    }
    
}

void testRespiration(void){
    unsigned int i, debugPoint, t;
    double currentData;
    unsigned char haveReference, apneaTrigger;
    double refRMS, temp;
    haveReference = apneaTrigger = 0;
    refRMS = 0;
    temp = 9001;
    i = 0;

    //Each sample of testWaveform is already at 2 Hz
    while(testWaveform[i] != 9001){
        currentData = fabs(testWaveform[i]);
               
        if(!haveReference){
            refRMS += pow(currentData, 2);
            LCDClear();
            LCDGoto(0, 0);
            printDouble(i, 2);
            LCDGoto(6, 0);
            printDouble(currentData, 2);

            if(i == 19){
                temp = (double) (i+1);
                refRMS /= temp;
                refRMS = sqrt(refRMS);
                haveReference = !haveReference;
            }
        } else{
            LCDClear();
            LCDGoto(0, 0);
            printDouble(i, 2);
            LCDGoto(6, 0);
            printDouble(currentData, 2);

            if(currentData < 0.95*refRMS){
                apneaTrigger++;

                debugPoint = 0;

                if(apneaTrigger == 12){

                    LCDGoto(0, 1);
                    printDouble(3.14, 2);
                    apneaTrigger = 0;

                    debugPoint = 0;

                }
            } else{
                apneaTrigger = 0;
            }
        }
        i++;
        Delay10KTCYx(20);
    }


}

void LCDOutputString(unsigned char buffer[]){
    unsigned int i;
    unsigned int buffer_length = strlen(buffer);

    for(i = 0; i < buffer_length; i++){
        LCDPutChar(buffer[i]);
    }
}






