/**
 *  @file ApneaMonitor.h
 *  @author Praveenanurag Dulapalli
 *  @date 2015-11-12
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
#include "Lcd.h" // Also includes "General.h" which we need for I/O constants
#include "DataManager.h"

#define APNEA_THRESHOLD_PERCENT 85 // Threshold below which stimulus triggered
#define APNEA_REFERENCE_DURATION 12 // time(sec) required for baseline reference
#define APNEA_DETECT_DURATION 2 // time(sec) required to clearly sense apnea
#define APNEA_STIMULATION_DURATION 3 // time(sec) required to stimulate
#define MEASUREMENT_STALL_DURATION 1 // time(sec) to wait for meaningful data
#define APNEA_STIMULATION_RECOVERY_DURATION 20 // time(sec) to wait before
                                               // checking for apnea after
                                               // stimulus
#define FAILURE_STATE_CRITERION_DURATION 10 // time(sec) to classify failure
#define STIMULUS_PIN LATEbits.LATE1
#define STIMULUS_HIGH_MICROS 300
#define STIMULUS_LOW_MICROS 19700

#define IS_NORMAL_RESP 0x0
#define IS_APNEA 0x1
#define IS_ERROR 0x2
#define RESET_REFERENCE 0x3

/**
 * @brief      Checks to see if user has entered a state of sleep apnea. If not,
 *             then determines if there is an error state or if it is necessary
 *             to re-calculate the reference respiration amplitude measurement.
 *
 * @return     the current state of the apnea monitor
 */
int checkApneaCondition(void); //Determine if patient has entered apnea state

/**
 * @brief      Send a 50 kHz, 1.5% duty cycle pulse to stimulate the
 *             hypoglossal nerve
 */
void sendStimulus(void); //Set designated I/O pin HIGH to activate stimulus

/**
 * @brief      Add interval between taking measurements equivalent to sample
 *             period
 */
void delayOneSamplePeriod(void);

/**
 * @brief      Include the specified measurement value in the reference
 *             threshold calculation
 *
 * @param      dataPoint  pointer to a structure holding a floating point
 *             respiration acceleration amplitude value
 */
void addToReferenceCalc(struct Data_Node *dataPoint);

/**
 * @brief      Begin re-calculation of the respiration acceleration amplitude
 *             reference
 */
void referenceReset(void);


#ifdef	__cplusplus
}
#endif

#endif	/* APNEAMONITOR_H */

