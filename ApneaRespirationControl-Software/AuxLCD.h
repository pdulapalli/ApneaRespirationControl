/**
 *  @file AuxLCD.h
 *  @author Praveenanurag Dulapalli
 *  @date 2015-11-22
 *  @brief Provides register information about ADXL313 accelerometer, and
 *  functions to access and make sense of accelerometer measurement data
 *
 *  @copyright Copyright 2015 Praveenanurag Dulapalli
 *  @license
 *  Licensed under the Apache License, Version 2.0 (the "License"); you may not
 *  use this file except in compliance with the License. You may obtain a copy of
 *  the License at <br><br>http://www.apache.org/licenses/LICENSE-2.0<br><br>
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 *  WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
 *  License for the specific language governing permissions and limitations under
 *  the License.}
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
 * @brief      Output a formatted character sequence to LCD, character-by-character
 *
 * @param      buffer  Formatted character sequence to display
 */
void LCDOutputString(unsigned char buffer[]);

/**
 * @brief      Perform necessary operations to output a floating point value
 *             to the LCD
 *
 * @param[in]  myDouble       floating point value to output
 * @param[in]  decimalPlaces  number of digits after decimal point to preserve
 */
void printDouble(double myDouble, int decimalPlaces);

#ifdef	__cplusplus
}
#endif

#endif	/* AUXLCD_H */

