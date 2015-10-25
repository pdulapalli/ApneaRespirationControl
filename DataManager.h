/*
 * File:   DataManager.h
 * Author: Praveenanurag Dulapalli
 *
 * Created: 09/27/2015
 * Last Modified: 10/11/2015
 */

#ifndef DATAMANAGER_H
#define	DATAMANAGER_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <p18f46k22.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <delays.h>

#include "ADXL313.h"
#include "Lcd.h" //Also includes "General.h" which we need for I/O constants

#define WINDOW_DURATION 10
#define SAMPLES_PER_SECOND 2
#define DATA_BITS_LENGTH 10 //Full resolution, left-justified 0.5 g measurement
                            //LSB will always be 0

struct Data_Node{
    AccelData axisMeasurements; //Contains the data 'packet' at this instant
    int most_recent; //A value of '1' indicates whether data is latest
    struct Data_Node *next; 
};

extern struct Data_Node sensor_data[WINDOW_DURATION*SAMPLES_PER_SECOND]; //Set up global variable for data acquisition
extern struct Data_Node *sensor_data_HEAD;
extern struct Data_Node *sensor_data_TAIL;

int checkBufferFull(void); //Determine whether buffer fully loaded
void addData(unsigned int dataToAdd); //Update data buffer contents
void removeData(unsigned int numElements);  //Remove oldest data
int latestData(void); //Locate index of most recent data
double digitalToAnalogValue(unsigned char dataBits_UPPER, unsigned char dataBits_LOWER);

#ifdef	__cplusplus
}
#endif

#endif	/* DATAWINDOW_H */

