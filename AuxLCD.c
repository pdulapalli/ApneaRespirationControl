#include "AuxLCD.h"

void LCDOutputString(unsigned char buffer[]){
    unsigned int i;
    unsigned int buffer_length = strlen(buffer);

    for(i = 0; i < buffer_length; i++){
        LCDPutChar(buffer[i]);
    }
}

void printDouble(double myDouble, int decimalPlaces){
    unsigned char buffer[31];
    long int_a, frac_a; // our integer and fractional temps
    int_a = myDouble; // standard C cast
    frac_a = (myDouble - int_a)*pow(10, (double) decimalPlaces); // expose up to 9 decimals
    frac_a = (frac_a < 0) ? -frac_a : frac_a; // if negative, change sign
    sprintf(buffer, "%ld.%ld", int_a, frac_a); // get the ascii
    LCDOutputString(buffer);
}
