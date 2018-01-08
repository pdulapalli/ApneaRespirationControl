/**
 *  @file AuxLCD.c
 *  @author Praveenanurag Dulapalli
 *  @date 2015-11-22
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
#include "AuxLCD.h"

void LCDOutputString(unsigned char buffer[]){
    unsigned int i, buffer_length;

    buffer_length = strlen(buffer); // Determine how many characters to output

    for(i = 0; i < buffer_length; i++){
        LCDPutChar(buffer[i]); // Call the provided Lcd.h library function
                               // for each character in the output buffer
    }
}

void printDouble(double myDouble, int decimalPlaces){
    unsigned char buffer[31];
    long int_a, frac_a; //Integer and fractional temps

    int_a = myDouble; //Cast double as int
    frac_a = (myDouble - int_a)*pow(10, (double) decimalPlaces); // Expose up to
                                                                 // 9 decimals
    frac_a = (frac_a < 0) ? -frac_a : frac_a; // If negative, change sign

    sprintf(buffer, "%ld.%ld", int_a, frac_a); // Store formatted double output
                                               // in ASCII buffer
    LCDOutputString(buffer); // Call the custom function for writing strings
                             // to LCD screen
}
