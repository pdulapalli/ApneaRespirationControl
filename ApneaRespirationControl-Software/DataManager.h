/**
 * File:   DataManager.h
 * Author: Praveenanurag Dulapalli
 *
 * Created: 09/27/2015
 * Last Modified: 11/11/2015
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

#define MEASUREMENT_WINDOW_DURATION     6 //Set the time duration that the measurement buffer spans
#define MEASUREMENT_SAMPLE_RATE         4 //Set the sampling rate to capture measurements
#define BUFFER_LENGTH                  MEASUREMENT_SAMPLE_RATE*MEASUREMENT_WINDOW_DURATION //Set size of buffer
#define DATA_BITS_LENGTH               12 //Full resolution, right-justified 2.0 g measurement
                                          //LSB will always be 0, MSB = sign bit

/**
*Function Name: initializeCircularBuffer
*Parameters:    None
*Output:        None
*Purpose:       Prepare a circular buffer with the specified size and initialize the associated
                pointers to the beginning and end of useful data
**/
void initializeCircularBuffer(void);

/**
*Function Name: checkBufferStatus
*Parameters:    None
*Output:        int bufferStatus: value indicating that the buffer is full, empty, or neither
*Purpose:       Determines how full the buffer is at some instant
**/
int checkBufferStatus(void); //Determine whether buffer fully loaded

/**
*Function Name: addDataAccel
*Parameters:    double dataToAdd: floating point number containing one point of respiration data
*Output:        struct Data_Node *sensor_measure_tail: pointer to the most recent data value
*Purpose:       Adds a data point to the circular buffer holding the measurements
**/
struct Data_Node *addDataAccel(double dataToAdd);

#ifdef	__cplusplus
}
#endif

#endif	/* DATAWINDOW_H */

