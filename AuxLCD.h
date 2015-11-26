/*
 * File:   AuxLCD.h
 * Author: Praveenanurag Dulapalli
 *
 * Created: 11/09/2015
 * Last Modified: 11/22/2015
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

#include "Lcd.h"            //Invoke core Lcd function library

/**
*Function Name: LCDOutputString
*Parameters:    unsigned char buffer[]: Formatted character sequence to display
*Output:        None
*Purpose:       Output a formatted character sequence to LCD, character-by-character
**/
void LCDOutputString(unsigned char buffer[]);

/**
*Function Name: printDouble
*Parameters:    [1] double myDouble: floating point value to output
                [2] int decimalPlaces: number of digits after decimal point to retain
*Output:        None
*Purpose:       Perform necessary operations to output a floating point value to the LCD
**/
void printDouble(double myDouble, int decimalPlaces);

#ifdef	__cplusplus
}
#endif

#endif	/* AUXLCD_H */

