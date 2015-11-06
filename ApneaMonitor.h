/*
 * File:   ApneaMonitor.h
 * Author: Praveenanurag Dulapalli
 *
 * Created: 09/27/2015
 * Last Modified: 09/27/2015
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

#define APNEA_THRESHOLD_PERCENT 70
#define APNEA_REFERENCE_DURATION 12
#define APNEA_DETECT_DURATION   2 //time required before declaring apnea condition
#define STIMULUS_PIN LATEbits.LATE1
#define STIMULUS_HIGH_MICROS    300
#define STIMULUS_LOW_MICROS     19700         
    
int isApneaCondition(void); //Determine if patient has entered apnea state
void sendStimulus(void); //Set designated I/O pin HIGH to activate stimulus
void delayOneSamplePeriod(void); //Performs calculation to space measurements with appropriate sample period
void addToReferenceCalc(struct Data_Node *dataPoint);

#ifdef	__cplusplus
}
#endif

#endif	/* APNEAMONITOR_H */

