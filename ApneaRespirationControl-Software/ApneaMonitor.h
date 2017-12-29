/**
 * File:   ApneaMonitor.h
 * Author: Praveenanurag Dulapalli
 *
 * Created: 09/27/2015
 * Last Modified: 11/12/2015
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

#ifndef APNEAMONITOR_H
#define	APNEAMONITOR_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "Globals.h"

#include <p18f46k22.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <delays.h>

#include "ADXL313.h"
#include "Lcd.h" //Also includes "General.h" which we need for I/O constants
#include "DataManager.h"

#define APNEA_THRESHOLD_PERCENT                85 //Trigger stimulation if most recent window completely drops below this
#define APNEA_REFERENCE_DURATION               12 //time(sec) required to establish reference
#define APNEA_DETECT_DURATION                   2 //time(sec) required before declaring apnea condition
#define APNEA_STIMULATION_DURATION              3 //time(sec) required to stimulate
#define MEASUREMENT_STALL_DURATION              1 //time(sec) to stall before meaningful measurement
#define APNEA_STIMULATION_RECOVERY_DURATION    20 //time(sec) to wait before checking for apnea after stimulus
#define FAILURE_STATE_CRITERION_DURATION       10 //time(sec) after which declare failure state
#define STIMULUS_PIN                          LATEbits.LATE1
#define STIMULUS_HIGH_MICROS                  300
#define STIMULUS_LOW_MICROS                 19700

#define IS_NORMAL_RESP                      0x0
#define IS_APNEA                            0x1
#define IS_ERROR                            0x2
#define RESET_REFERENCE                     0x3

/**
*Function Name: checkApneaCondition
*Parameters:    None
*Output:        int current_condition: the current state of the apnea monitor
*Purpose:       Checks to see if user has entered a state of sleep apnea. If not, then
                determines if there is an error state or if it is necessary to re-calculate
                the reference respiration amplitude measurement.
**/
int checkApneaCondition(void); //Determine if patient has entered apnea state

/**
*Function Name: sendStimulus
*Parameters:    None
*Output:        None
*Purpose:       Send a 50 kHz, 1.5% duty cycle pulse to stimulate the hypoglossal nerve
**/
void sendStimulus(void); //Set designated I/O pin HIGH to activate stimulus

/**
*Function Name: delayOneSamplePeriod
*Parameters:    None
*Output:        None
*Purpose:       Add interval between taking measurements equivalent to sample period
**/
void delayOneSamplePeriod(void);

/**
*Function Name: addToReferenceCalc
*Parameters:    struct Data_Node *dataPoint: pointer to a structure holding a floating
                                             point respiration acceleration amplitude value
*Output:        None
*Purpose:       Include the specified measurement value in the reference threshold calculation
**/
void addToReferenceCalc(struct Data_Node *dataPoint);

/**
*Function Name: referenceReset
*Parameters:    None
*Output:        None
*Purpose:       Begin re-calculation of the respiration acceleration amplitude reference
**/
void referenceReset(void);


#ifdef	__cplusplus
}
#endif

#endif	/* APNEAMONITOR_H */

