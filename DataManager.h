/*
 * File:   DataManager.h
 * Author: Praveenanurag Dulapalli
 *
 * Created: 09/27/2015
 * Last Modified: 11/11/2015
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

#define MEASUREMENT_WINDOW_DURATION     6  
#define MEASUREMENT_SAMPLE_RATE         4  
#define BUFFER_LENGTH                  MEASUREMENT_SAMPLE_RATE*MEASUREMENT_WINDOW_DURATION
#define DATA_BITS_LENGTH               12 //Full resolution, right-justified 2.0 g measurement
                                          //LSB will always be 0, MSB = sign bit
       
void initializeCircularBuffer(void);
void storeReferenceData(void);
int checkBufferStatus(void); //Determine whether buffer fully loaded
struct Data_Node *addDataAccel(double dataToAdd); //Update data buffer contents
void addDataTest(double dataToAdd); //Add non-accelerometer test data to buffer
void removeData(unsigned int numElements);  //Remove oldest data

#ifdef	__cplusplus
}
#endif

#endif	/* DATAWINDOW_H */

