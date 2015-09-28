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

#include <p18f46k22.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <delays.h>

#include "Lcd.h"
#include "DataWindow.h"

#define APNEA_THRESHOLD_PERCENT 70
#define REQ_APNEA_ONSET_DURATION 2 //time required before declaring apnea condition

int isApneaCondition(void); //Determine if patient has entered apnea state
void sendStimulus(void); //Set designated I/O pin HIGH to activate stimulus
int computeAmplitude(Data_Node dataPoint); //Perform calculation to obtain amplitude of displacement

#ifdef	__cplusplus
}
#endif

#endif	/* APNEAMONITOR_H */

