/* 
 * File:   main.c
 * Author: Praveenanurag Dulapalli
 *
 * Created: 09/26/2015
 */


#include <p18f46k22.h>
#include <stdio.h>
#include <stdlib.h>
#include <delays.h>

#include "Lcd.h"


void main() {
    OSCCON = 0b01010110; //4 MHz internal oscillator

    //Set up LCD
    ANSELD = 0x00;
    TRISD = 0x00; //Digital out
}

