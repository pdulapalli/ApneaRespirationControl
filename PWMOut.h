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
    
#include <p18f46k22.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <delays.h>
#include <pwm.h>
#include <timers.h>
    
void initializePWM(int prescaleFactor);
void writePWM(double valueToWrite);

#ifdef	__cplusplus
}
#endif

#endif	/* PWMOUT_H */

