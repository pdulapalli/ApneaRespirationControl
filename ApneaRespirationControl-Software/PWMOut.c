/**
 * File:   PWMOut.c
 * Author: Praveenanurag Dulapalli
 *
 * Created: 11/16/2015
 * Last Modified: 11/22/2015
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

#include "PWMOut.h"

void initializePWM(int prescaleFactor, double PWMFreq, double clockSpeed){
    double PR2val, clockPeriod, PWMPeriod;
    int PR2bitVal;

    //Enable PWM ports
    TRISEbits.TRISE2 = OUTPUT;
    LATEbits.LATE2 = LOW;

    //Obtain period information
    clockPeriod = 1/clockSpeed;
    PWMPeriod = 1/PWMFreq;

    //PWM period = [(PR2) + 1] * 4 * TOSC * (TMR2 prescale value)

    //Timer2 Period
    PR2val = PWMPeriod;
    PR2val /= 4*clockPeriod*prescaleFactor;
    PR2val--;

    PR2bitVal = (int) PR2val;
    PR2bitVal = PR2bitVal & 0xFF;

    PR2 = PR2bitVal;

    //Select Timer2 for CCP5 PWM Module
    CCPTMRS1bits.C5TSEL = 0b00;

    //Enable Timer2
    T2CONbits.T2OUTPS = 0x0;
    T2CONbits.TMR2ON = HIGH;
    T2CONbits.T2CKPS = 0b11;
}

void writePWM(unsigned int dutyCycleBits){
    unsigned int CCPR5Lval, CCP5CONval;

    //Determine bit settings for CCP registers
    CCPR5Lval = (dutyCycleBits & 0x3FC) >> 2;
    CCP5CONval = (dutyCycleBits & 0x03) << 4;

    //Write appropriate values to CCP registers
    CCPR5L = CCPR5Lval;
    CCP5CON = (CCP5CONval & 0x30) | 0xC;
}

void closePWM(void){
    //Disable CCP5 PWM pins
    LATEbits.LATE2 = LOW;
    TRISEbits.TRISE2 = INPUT;

    //Reset Timer2 and CCP5 registers
    T2CON = 0x00;
    CCPR5L = 0x00;
    CCP5CON = 0x00;
}

int convertAccelDataToDutyCycle(double myValue, double maxVal, int prescaleFactor, double PWMFreq, double clockSpeed){
    double dutyTemp, clockPeriod, PWMPeriod;
    unsigned int dataOut;

    //Convert rates to times
    clockPeriod = 1/clockSpeed;
    PWMPeriod = 1/PWMFreq;

    dutyTemp = floor((fabs(myValue))); //Round actual accelerometer measurement down to closest integer
    dutyTemp /= maxVal; //Normalize measurement by specified maximum value
    dutyTemp *= PWMPeriod; //Multiply duty cycle by PWM period
    dutyTemp /= clockPeriod*prescaleFactor; //Additional computation to account for Timer settings

    dataOut = (unsigned int) dutyTemp; //Convert from double to int
    dataOut = dataOut & 0x3FF; //Extract 10-bit value

    return dataOut;
}