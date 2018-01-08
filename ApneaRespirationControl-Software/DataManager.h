/**
 *  @file DataManager.h
 *  @author Praveenanurag Dulapalli
 *  @date 2015-11-11
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

#ifndef DATAMANAGER_H
#define	DATAMANAGER_H

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

#define MEASUREMENT_WINDOW_DURATION 6 // Set the measurement buffer's time span
#define MEASUREMENT_SAMPLE_RATE 4 // Set the sampling rate for measurements
#define BUFFER_LENGTH MEASUREMENT_SAMPLE_RATE*MEASUREMENT_WINDOW_DURATION
#define DATA_BITS_LENGTH 12 // Full resolution, right-justified 2.0g measurement
                            // LSB will always be 0, MSB = sign bit

/**
 * @brief      Prepare a circular buffer with the specified size and initialize
 *             the associated pointers to the beginning and end of useful data
 */
void initializeCircularBuffer(void);

/**
 * @brief      Determines how full the buffer is at some instant
 *
 * @return     value indicating the buffer is full(1), empty(2), or neither(3)
 */
int checkBufferStatus(void); //Determine whether buffer fully loaded

/**
 * @brief      Adds a data point to the circular buffer holding the measurements
 *
 * @param[in]  dataToAdd  floating point number containing one point of
 *                        respiration data
 *
 * @return     pointer to the most recent data value
 */
struct Data_Node *addDataAccel(double dataToAdd);

#ifdef	__cplusplus
}
#endif

#endif	/* DATAWINDOW_H */

