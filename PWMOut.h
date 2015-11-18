/* 
 * File:   PWMOut.h
 * Author: pdulapalli
 *
 * Created on November 16, 2015, 11:14 AM
 */

#ifndef PWMOUT_H
#define	PWMOUT_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "Globals.h"
    
#include "General.h"
    
#include <p18f46k22.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <delays.h>
#include <pwm.h>
#include <timers.h>
    
#define CLOCK_8_MHz 8000000
#define TIMER2_PRESCALE_16 16
#define PWM_FREQ_1_KHz   1000   
#define MAX_1500_MILLI_G    1500
    
void initializePWM(int prescaleFactor, double PWMFreq, double clockSpeed);
void writePWM(int dutyCycleBits);
int convertAccelDataToDutyCycle(double myValue, double maxVal, int prescaleFactor, double PWMFreq, double clockSpeed);
void closePWM(void);

#ifdef	__cplusplus
}
#endif

#endif	/* PWMOUT_H */

