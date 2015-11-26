#include "AuxLCD.h"

void LCDOutputString(unsigned char buffer[]){
    unsigned int i, buffer_length;

    buffer_length = strlen(buffer); //Determine how many characters to output

    for(i = 0; i < buffer_length; i++){
        LCDPutChar(buffer[i]); //Call the provided Lcd.h library function
                               //for each character in the output buffer
    }
}

void printDouble(double myDouble, int decimalPlaces){
    unsigned char buffer[31];
    long int_a, frac_a; //Integer and fractional temps

    int_a = myDouble; //Cast double as int
    frac_a = (myDouble - int_a)*pow(10, (double) decimalPlaces); //Expose up to 9 decimals
    frac_a = (frac_a < 0) ? -frac_a : frac_a; //If negative, change sign

    sprintf(buffer, "%ld.%ld", int_a, frac_a); //Store formatted double output in ASCII buffer
    LCDOutputString(buffer); //Call the custom function for writing strings to LCD screen
}
