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

#include "SerialSPI.h" //Handle SPI Serial communication between PIC Master and ADXL313 Slave
#include "DataWindow.h" //Manage access, updating, and organization of data via circular buffer
#include "ApneaMonitor.h" //Amplitude detection to alert if user in apnea condition

extern int current_state; //Tracking variable to manage what state device currently in

void main() {
    OSCCON = 0b01010110; //4 MHz internal oscillator

    //Set up LCD
    ANSELD = 0x00;
    TRISD = 0x00; //Digital out

    current_state = 0;

    /**
    *CODE OUTLINE:
    *   [1] Idle until user activates system
    *   [2] Establish SPI serial connection between PIC18F46K22 (Master) and ADXL313 (Slave)
    *   [3] Initialize circular buffer and collect data until buffer is fully loaded
    *   [4] Extract x, y, z, components of data and compute amount of displacement
    *           *For first full set of samples, compute the mean
        [5] Continue to collect data into buffer and repeating step [4] as necessary
    *   [6] If amplitude falls below certain percentage threshold (of mean), set stimulus I/O Pin HIGH
    */
}


