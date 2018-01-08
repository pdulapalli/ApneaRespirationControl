 /**
 *  @file PWMOut.h
 *  @author Praveenanurag Dulapalli
 *  @date 2015-11-22
 *  @brief Provides register information about ADXL313 accelerometer, and
 *  functions to access and make sense of accelerometer measurement data
 *
 *  @copyright Copyright 2015 Praveenanurag Dulapalli
 *  @license
 *  Licensed under the Apache License, Version 2.0 (the "License"); you may not
 *  use this file except in compliance with the License. You may obtain a copy of
 *  the License at <br><br>http://www.apache.org/licenses/LICENSE-2.0<br><br>
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 *  WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
 *  License for the specific language governing permissions and limitations under
 *  the License.}
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
#define PWM_FREQ_1_KHz 1000 //1 KHz PWM carrier frequency
#define MAX_1500_MILLI_G 1500 //1500 mG corresponding to 100% duty cycle

/**
 * @brief      Activate registers and I/O pins associated with PWM (CCP5)
 *
 * @param[in]  prescaleFactor  factor to scale PWM clock speed
 * @param[in]  PWMFreq         PWM carrier frequency
 * @param[in]  clockSpeed      PWM clock speed setting
 */
void initializePWM(int prescaleFactor, double PWMFreq, double clockSpeed);

/**
 * @brief      Output a PWM pulse with the specified duty cycle setting
 *
 * @param[in]  dutyCycleBits  bit sequence value representing duty cycle
 */
void writePWM(unsigned int dutyCycleBits);

/**
 * @brief      Compute a duty cycle and convert it to appropriate bit sequence
 *             from original data
 *
 * @param[in]  myValue         accelerometer respiration displacement reading
 * @param[in]  maxVal          maximum expected measurement (normalization
 *                             factor)
 * @param[in]  prescaleFactor  factor to scale PWM clock speed
 * @param[in]  PWMFreq         PWM carrier frequency
 * @param[in]  clockSpeed      PWM clock speed setting
 *
 * @return     { description_of_the_return_value }
 */
int convertAccelDataToDutyCycle(double myValue, double maxVal,
                                int prescaleFactor, double PWMFreq,
                                double clockSpeed);

/**
 * @brief      Deactivate CCP module--reset registers and associated PWM pins
 */
void closePWM(void);

#ifdef	__cplusplus
}
#endif

#endif	/* PWMOUT_H */

