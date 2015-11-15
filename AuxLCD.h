/* 
 * File:   AuxLCD.h
 * Author: Praveenanurag Dulapalli
 *
 * Created: 11/09/2015
 */

#ifndef AUXLCD_H
#define	AUXLCD_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "Globals.h"

#include <p18f46k22.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <delays.h>
#include <string.h>

#include "Lcd.h"            //Utilize LCD Display if needed
    
void LCDOutputString(unsigned char buffer[]);
void printDouble(double myDouble, int decimalPlaces);

#ifdef	__cplusplus
}
#endif

#endif	/* AUXLCD_H */

