/*
 * File:   ApneaMonitor.h
 * Author: Praveenanurag Dulapalli
 *
 * Created: 09/27/2015
 * Last Modified: 11/12/2015
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
    
    
int checkApneaCondition(void); //Determine if patient has entered apnea state
void sendStimulus(void); //Set designated I/O pin HIGH to activate stimulus
void delayOneSamplePeriod(void); //Performs calculation to space measurements with appropriate sample period
void addToReferenceCalc(struct Data_Node *dataPoint);
int readyToMeasure(void);


#ifdef	__cplusplus
}
#endif

#endif	/* APNEAMONITOR_H */

