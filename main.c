/*
 * File:   main.c
 * Author: Praveenanurag Dulapalli
 *
 * Created: 09/26/2015
 * Last Modified: 11/14/2015
 */

#include <p18f46k22.h>
#include <stdio.h>
#include <stdlib.h>
#include <delays.h>
#include <string.h>
#include <math.h>

#include "Globals.h"        //Contains shared variables, constants, and functions
#include "Lcd.h"            //Functions for LCD use
#include "AuxLCD.h"         //Custom additional functionality for LCD Printing
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
#define STATE_ERROR_CHECK           0x4
#define STATE_UPDATE_DATA           0x5
#define STATE_APNEA_DETECTION       0x6
#define STATE_STIMULATE_NERVE       0x7
#define STATE_TEST_THRESHOLD        0x8

unsigned int current_state; //Tracking variable to manage what device's current state

    /**
    *CODE OUTLINE:
    *   [1] Idle until user activates system
    *   [2] Establish SPI serial connection between PIC18F46K22 (Master) and ADXL313 (Slave)
    *   [3] Initialize circular buffer and collect data until buffer is fully loaded
    *   [4] Extract x, y, z, components of data and compute amount of displacement
    *           *For first two full sets of samples, compute the RMS
        [5] Continue to collect data into buffer and repeating step [4] as necessary
    *   [6] If amplitude falls below certain percentage threshold (of mean), pulse stimulus I/O pin
    */

void initializeSystems(void);
void initalizePWM(double dutyCycle, double Tosc, double FreqPWM, double prescaleFactor);
void writePWM(double outputValue, double outputRange, double Tosc, double prescaleFactor);
void measureAndDisplay(void);

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
}

void main() {
    int i; //Index counter
    int apneaBoolean, inttemp;
    unsigned int uinttemp;
    AccelData currentAxes;
    struct Data_Node *currentDataPoint;
    double currentMeas, displacement, doubletemp, q;
    i = 0;
    displacement = 0;
    current_state = STATE_INITIALIZE;

    while(testWaveform[i] != 9001){
        //BEGIN State Machine
        switch(current_state){
            case STATE_IDLE:
                break;

            case STATE_INITIALIZE:
                initializeSystems();

                //Grace period to prime ADXL before recording measurements
                measurementGracePeriod(12, ADXL313_TWO_G_RANGE);

                current_state = STATE_IDLE;
                break;

            case STATE_MEASURE:
                currentAxes = readAxisMeasurements();

                current_state = STATE_CALCULATE;
                break;

            case STATE_CALCULATE:
                displacement = computeAmplitude(currentAxes, ADXL313_TWO_G_RANGE);

                current_state = STATE_ERROR_CHECK;
                break;

            case STATE_ERROR_CHECK:
                LCDGoto(0, 0);
                printDouble(1000*displacement, 3);

                LCDGoto(0, 1);
                q = digitalToAnalogMeasurement(currentAxes.z_axis, 2);
                printDouble(1000*q, 3);

                current_state = STATE_UPDATE_DATA;
                break;

            case STATE_UPDATE_DATA:
                currentDataPoint = addDataAccel(displacement);

                if(!referenceExists){
                    addToReferenceCalc(currentDataPoint);
                }

                current_state = STATE_APNEA_DETECTION;
                break;

            case STATE_APNEA_DETECTION:
                apneaBoolean = isApneaCondition();

                current_state = STATE_STIMULATE_NERVE;
                break;

            case STATE_STIMULATE_NERVE:
                if(apneaBoolean){
                    sendStimulus();
                    measurementGracePeriod(20, ADXL313_TWO_G_RANGE);
                }

                delayOneSamplePeriod();

                current_state = STATE_MEASURE;
                break;

            case STATE_TEST_THRESHOLD:
                measureAndDisplay();
                Delay10KTCYx(0);
                break;

            default:
                break;
        }
    }
}

void initializeSystems(void){
    initializePIC();
    initializeSPI();
    initializeADXL313();
    initializeCircularBuffer();
}

void initalizePWM(double dutyCycle, double Tosc, double FreqPWM, double prescaleFactor){
    double PWMPeriod, PR2Val, CCPVal;

    PWMPeriod = 1/FreqPWM;
    PR2Val = -1 + PWMPeriod/(4*Tosc*prescaleFactor);

    TRISCbits.RC2 = OUTPUT;  //RC2 = CCP1 port
    PORTCbits.RC2 = LOW;

    T2CON = 0b00000111; //[b7 = 0; b6:3 = postscaler select, b2 = timer on/off, b1:0 = prescaler select]
                        //1 to 1 postscaler, timer2 ON, 16 prescaler
    PR2 = 0b1111011;    //Timer2 Period Register
                        //Calculated Value = 124
                        //PR2 = [PWMPeriod/(4*Tosc*TMRPrescale)] - 1
                        //CCPR1L:CCP1CON[5:4] = [DutyCycle/(Tosc*TMRPrescale)
                        //Calculated Value = 250

    CCPVal = dutyCycle/(Tosc*prescaleFactor);
    CCPR1L = 0b00111110; //8 MSB of calculated duty cycle
    CCP1CON = 0b00101100;//PWM mode in b5:4 = 2 LSB of calculated duty cycle
                         //Mode select bits b3:0 = (1100) PWM Mode
}

void writePWM(double outputValue, double outputRange, double Tosc, double prescaleFactor){
    double dutyCycle, CCPVal;

    dutyCycle = outputValue/outputRange;
    CCPVal = dutyCycle/(Tosc*prescaleFactor);
    //TODO:

    CCPR1L = 0b00111110; //8 MSB of calculated duty cycle
    CCP1CON = 0b00101100;//PWM mode in b5:4 = 2 LSB of calculated duty cycle
                         //Mode select bits b3:0 = (1100) PWM Mode
}

void measureAndDisplay(void){
    unsigned int i, q, debugger;
    unsigned char dataBuffer[31];
    unsigned char currentEntry;
    unsigned char LCD_string_buffer[31]; //General purpose LCD output buffer
    double analogValue;

    SPI_Read_Multiple(REG_ADDR_ADXL313_DATA_X0, 6, dataBuffer);

    q = concatenateRawValues(dataBuffer[5], dataBuffer[4]);

    LCDClear();

    LCDGoto(0, 0);
    sprintf(LCD_string_buffer, "0x%04X \0", q);
    LCDOutputString(LCD_string_buffer);

    LCDGoto(0, 1);
    analogValue = digitalToAnalogMeasurement(q, 2);
    printDouble(analogValue, 2);

    Delay1KTCYx(0);
}