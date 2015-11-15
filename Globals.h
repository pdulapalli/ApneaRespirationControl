/*
 * File:   Globals.h
 * Author: pdulapalli
 *
 * Created: 10/26/2015
 */

#ifndef GLOBALS_H
#define	GLOBALS_H

#ifdef	__cplusplus
extern "C" {
#endif

#define nop() _asm nop _endasm
#define NOP_PER_MS 73
#define NOP_PER_300_US 21
#define NOP_PER_19700_US 1438
#define NOP_PER_50_MS 3340
    
#include <delays.h>

extern unsigned int current_state; //State machine's current state

/*-----ADXL313.h------*/
typedef struct{
    unsigned int x_axis;
    unsigned int y_axis;
    unsigned int z_axis;
} AccelData;

/*-----DataManager.h-----*/
struct Data_Node{
    double respDisplacement;
    struct Data_Node *next;
};

extern int sample_period;

extern struct Data_Node *sensor_measure_buffer; //Set up global variable for data acquisition
extern struct Data_Node *sensor_measure_HEAD;   //Circular buffer head pointer
extern struct Data_Node *sensor_measure_TAIL;   //Circular buffer tail pointer

/*-----ApneaMonitor.h-----*/
extern double breathingDisplacementReference;
extern char referenceExists; //'1' if already have reference measurement; '0' otherwise
extern char measurementReady; 

void delay_nops(int numNops);
void delay_ms(int numMillis);
void delay_50ms(int num50Millis);

/*-----VARIABLES IN EEPROM-----*/

extern const rom double testWaveform[];
extern double testSampleRate;

#ifdef	__cplusplus
}
#endif

#endif	/* GLOBALS_H */
