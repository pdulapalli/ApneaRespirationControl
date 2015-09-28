/*
 * File:   DataWindow.h
 * Author: Praveenanurag Dulapalli
 *
 * Created: 09/27/2015
 * Last Modified: 09/27/2015
 */

#ifndef DATAWINDOW_H
#define	DATAWINDOW_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <p18f46k22.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <delays.h>

#include "Lcd.h"

#define WINDOW_DURATION 10
#define SAMPLES_PER_SECOND 2

typedef struct {
    int value; //Contains the data 'packet' at this instant
    int most_recent; //A value of '1' indicates whether data is latest
} Data_Node;

extern Data_Node sensor_data[WINDOW_DURATION*SAMPLES_PER_SECOND]; //Set up global variable for data acquisition

int checkWindowFull(void); //Determine whether buffer fully loaded
void addData(int dataToAdd, int whereToAdd); //Update data buffer contents
int latestData(void); //Locate index of most recent data

#ifdef	__cplusplus
}
#endif

#endif	/* DATAWINDOW_H */

