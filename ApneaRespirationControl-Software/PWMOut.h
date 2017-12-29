/**
 * File:   PWMOut.h
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

#ifndef PWMOUT_H
#define	PWMOUT_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "Globals.h"

#include "General.h"

#include <p18f46k22.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <delays.h>
#include <pwm.h>
#include <timers.h>

#define CLOCK_8_MHz 8000000 //8 MHz Clock Speed
#define TIMER2_PRESCALE_16 16 //Prescale factor of 16 for Timer2 speed division
#define PWM_FREQ_1_KHz   1000 //1 KHz PWM carrier frequency
#define MAX_1500_MILLI_G  1500 //1500 mG corresponding to 100% duty cycle

/**
*Function Name: initializePWM
*Parameters:    [1] int prescaleFactor: factor to scale PWM clock speed
                [2] double PWMFreq: PWM carrier frequency
                [3] double clockSpeed: PWM clock speed setting
*Output:        None
*Purpose:       Activate registers and I/O pins associated with PWM (CCP5)
**/
void initializePWM(int prescaleFactor, double PWMFreq, double clockSpeed);

/**
*Function Name: writePWM
*Parameters:    unsigned int dutyCycleBits: bit sequence value representing duty cycle
*Output:        None
*Purpose:       Output a PWM pulse with the specified duty cycle setting
**/
void writePWM(unsigned int dutyCycleBits);

/**
*Function Name: convertAccelDataToDutyCycle
*Parameters:    [1] double myValue: original accelerometer respiration displacement measurement
                [2] double maxVal: maximum expected measurement (normalization factor)
                [3] int prescaleFactor: factor to scale PWM clock speed
                [4] double PWMFreq: PWM carrier frequency
                [5] double clockSpeed: PWM clock speed setting
*Output:        None
*Purpose:       Compute a duty cycle and convert it to appropriate bit sequence from original data
**/
int convertAccelDataToDutyCycle(double myValue, double maxVal, int prescaleFactor, double PWMFreq, double clockSpeed);

/**
*Function Name: closePWM
*Parameters:    None
*Output:        None
*Purpose:       Deactivate CCP module--reset registers and associated PWM pins
**/
void closePWM(void);

#ifdef	__cplusplus
}
#endif

#endif	/* PWMOUT_H */

