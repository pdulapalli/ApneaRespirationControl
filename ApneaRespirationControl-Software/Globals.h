/*
 * File:   Globals.h
 * Author: Praveenanurag Dulapalli
 *
 * Created: 10/26/2015
 * Last Modified: 11/26/2015
 */

#ifndef GLOBALS_H
#define	GLOBALS_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <delays.h>

#define nop() _asm nop _endasm //Create a macro to call a no-operation
                               //(processor does nothing for one cycle)

/*---Delay Durations Defined in Nops---*/
#define NOP_PER_MS 73
#define NOP_PER_300_US 21
#define NOP_PER_19700_US 1438
#define NOP_PER_50_MS 3340

extern unsigned int current_state; //State machine's current state

/*-----ADXL313.h------*/
//Structure that contains the three 16-bit values for axis acceleration measurements
typedef struct{
    unsigned int x_axis;
    unsigned int y_axis;
    unsigned int z_axis;
} AccelData;

/*-----DataManager.h-----*/
//Structure that contains the calculated respiration acceleration amplitude to form a circular buffer
struct Data_Node{
    double respDisplacement;
    struct Data_Node *next;
};

extern int sample_period;

extern struct Data_Node *sensor_measure_buffer; //Set up global variable for data acquisition
extern struct Data_Node *sensor_measure_HEAD;   //Circular buffer head pointer
extern struct Data_Node *sensor_measure_TAIL;   //Circular buffer tail pointer

/*-----ApneaMonitor.h-----*/
extern double breathingDisplacementReference; //Reference threshold to use for detecting apnea
extern char referenceExists; //'1' if already have reference measurement; '0' otherwise
extern char mostRecentCondition; //boolean to track most recent state of patient
extern int samplesSinceLastStim; //how many samples have occurred between previous stimulation

/**
*Function Name: delay_nops
*Parameters:    int numNops: how many no-operations to delay
*Output:        None
*Purpose:       Delay by a specified number of operations
**/
void delay_nops(int numNops);

/**
*Function Name: delay_ms
*Parameters:    int numMillis: how many milliseconds to delay
*Output:        None
*Purpose:       Delay by a specified duration of milliseconds
**/
void delay_ms(int numMillis);

/**
*Function Name: delay_50ms
*Parameters:    int num50Millis: how many multiples of 50 milliseconds to delay
*Output:        None
*Purpose:       Delay by a specified duration of (multiples of 50) milliseconds
**/
void delay_50ms(int num50Millis);

/*-----VARIABLES IN EEPROM-----*/
extern const rom double testWaveform[]; //Data for a test waveform to assess data processing
extern double testSampleRate; //Sample rate for the test waveform data

#ifdef	__cplusplus
}
#endif

#endif	/* GLOBALS_H */

