/**
 * File:   main.c
 * Author: Praveenanurag Dulapalli
 *
 * Created: 09/26/2015
 * Last Modified: 11/26/2015
 *
 * Copyright 2015 Praveenanurag Dulapalli
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may not
 * use this file except in compliance with the License. You may obtain a copy of
 * the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
 * License for the specific language governing permissions and limitations under
 * the License.
 */

#include <p18f46k22.h>
#include <stdio.h>
#include <stdlib.h>
#include <delays.h>
#include <string.h>
#include <timers.h>
#include <math.h>
#include <pwm.h>

#include "Globals.h"        //Contains shared variables, constants, and functions
#include "Lcd.h"            //Functions for LCD use
#include "AuxLCD.h"         //Custom additional functionality for LCD Printing
#include "SPIComLink.h"     //Handle SPI Serial communication between PIC Master and ADXL313 Slave
#include "DataManager.h"    //Manage access, updating, and organization of data via circular buffer
#include "ApneaMonitor.h"   //Amplitude detection to alert if user in apnea condition
#include "ADXL313.h"        //ADLX313 functions, register definitions, and bit configurations
#include "PWMOut.h"         //Functions to handle PWM output corresponding to measurements

#pragma config FOSC = INTIO7   // Internal OSC block, Port Function on RA6/7
#pragma config WDTEN = OFF     // Watch Dog Timer disabled
#pragma config XINST = OFF     // Disable extended instruction set (increase stack frame)

#pragma config PLLCFG = OFF
#pragma config BOREN = OFF
#pragma config MCLRE = EXTMCLR
#pragma config LVP = OFF
#pragma config PBADEN = OFF

/*-----STATE MACHINE CONDITIONS-----*/

#define STATE_IDLE                  0x0
#define STATE_INITIALIZE            0x1
#define STATE_MEASURE               0x2
#define STATE_CALCULATE             0x3
#define STATE_ERROR_CHECK           0x4
#define STATE_UPDATE_DATA           0x5
#define STATE_APNEA_DETECTION       0x6
#define STATE_STIMULATE_NERVE       0x7
#define STATE_PRINT_DISPLAY         0x8

unsigned int current_state; //Tracking variable to manage device's current state

    /**
    *CODE OUTLINE:
    *   [1] Idle until user activates system
    *   [2] Establish SPI serial connection between PIC18F46K22 (Master) and ADXL313 (Slave)
    *   [3] Initialize circular buffer and collect data until buffer is fully loaded
    *   [4] Extract x, y, z, components of data and compute amount of displacement
    *           *For first 12 seconds of samples, compute the RMS
        [5] Continue to collect data into buffer and repeat step [4] as necessary
    *   [6] If amplitude falls below certain threshold (of reference), activate stimulus pulse
    */

void initializePIC(void){

    //Set up 8 MHz internal oscillator
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

    //Activate stimulation pin
    TRISEbits.TRISE1 = OUTPUT;
    LATEbits.LATE1 = LOW;

    //Auxiliary pin for testing device
    TRISEbits.TRISE0 = OUTPUT;
    LATEbits.LATE0 = LOW;

}

void initializeSystems(void){
    initializePIC();
    initializePWM(TIMER2_PRESCALE_16, PWM_FREQ_1_KHz, CLOCK_8_MHz);
    initializeSPI();
    initializeADXL313();
    initializeCircularBuffer();
}

void main() {
    int i, apneaBoolean, inttemp;
    unsigned int uinttemp;
    AccelData currentAxes;
    struct Data_Node *currentDataPoint;
    double currentMeas, displacement, doubletemp, q;

    i = 0;
    displacement = 0;

    current_state = STATE_INITIALIZE;

    while(1){
        switch(current_state){
            case STATE_IDLE:
                Delay10KTCYx(0); //Delay before starting device so user can begin sleeping
                break;

            case STATE_INITIALIZE:
                initializeSystems();

                //Grace period to prime ADXL313 before recording measurements
                LCDClear();
                LCDGoto(0, 0);
                LCDWriteStr("Activating..");
                measurementGracePeriod(12, ADXL313_TWO_G_RANGE);

                current_state = STATE_MEASURE;
                break;

            case STATE_MEASURE:
                currentAxes = readAxisMeasurements();

                current_state = STATE_CALCULATE;
                break;

            case STATE_CALCULATE:
                displacement = computeAmplitude(currentAxes, ADXL313_TWO_G_RANGE);

                current_state = STATE_UPDATE_DATA;
                break;

            case STATE_UPDATE_DATA:
                currentDataPoint = addDataAccel(displacement);

                if(!referenceExists){
                    addToReferenceCalc(currentDataPoint);
                }

                current_state = STATE_APNEA_DETECTION;
                break;

            case STATE_PRINT_DISPLAY:
                LCDClear();
                LCDGoto(0, 0);
                printDouble(1000*displacement, 3);

                LCDGoto(9, 0);

                if(referenceExists){
                    printDouble(1000*breathingDisplacementReference, 1);
                } else{
                    LCDWriteStr("REF");
                }

                LCDGoto(0, 1);
                q = digitalToAnalogMeasurement(currentAxes.z_axis, 2);
                printDouble(1000*q, 3);

                inttemp = convertAccelDataToDutyCycle(1000*displacement, MAX_1500_MILLI_G, TIMER2_PRESCALE_16, PWM_FREQ_1_KHz, CLOCK_8_MHz);
                writePWM(inttemp);

                current_state = STATE_APNEA_DETECTION;
                break;

            case STATE_APNEA_DETECTION:
                apneaBoolean = checkApneaCondition();

                current_state = STATE_ERROR_CHECK;
                break;

            case STATE_ERROR_CHECK:
                if(apneaBoolean == IS_ERROR){
                    closePWM();

                    while(1){
                        LATEbits.LATE0 = HIGH;
                        Delay10TCYx(0);
                        LATEbits.LATE0 = LOW;
                        Delay10TCYx(0);
                        LCDClear();
                        LCDGoto(0, 0);
                        LCDWriteStr(">>>ERROR>>>");
                    }

                }

                current_state = STATE_STIMULATE_NERVE;
                break;

            case STATE_STIMULATE_NERVE:
                if(apneaBoolean == IS_APNEA){
                    LCDGoto(9, 1);
                    LCDWriteStr("STIM");
                    sendStimulus(); //Stimulation pulse!

                    LCDClear();
                    LCDGoto(0, 0);
                    LCDWriteStr("Warning standby");
                    writePWM(0);
                    measurementGracePeriod(10, ADXL313_TWO_G_RANGE); //Flush buffer with 10 seconds of unmonitored data

                } else if(apneaBoolean == RESET_REFERENCE){
                    referenceReset();
                }

                delayOneSamplePeriod();

                current_state = STATE_MEASURE;
                break;

            default:
                break;
        }
    }
}