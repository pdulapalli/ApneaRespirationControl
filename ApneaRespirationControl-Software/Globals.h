 /**
 *  @file Globals.h
 *  @author Praveenanurag Dulapalli
 *  @date 2015-11-26
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

#ifndef GLOBALS_H
#define	GLOBALS_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <delays.h>

#define nop() _asm nop _endasm // Create a macro to call a no-operation
                               // (processor does nothing for one cycle)

/*---Delay Durations Defined in Nops---*/
#define NOP_PER_MS 73
#define NOP_PER_300_US 21
#define NOP_PER_19700_US 1438
#define NOP_PER_50_MS 3340

extern unsigned int current_state; // State machine's current state

/*-----ADXL313.h------*/
// Structure that contains the three 16-bit values for axis acceleration
// measurements
typedef struct{
    unsigned int x_axis;
    unsigned int y_axis;
    unsigned int z_axis;
} AccelData;

/*-----DataManager.h-----*/
// Structure that contains the calculated respiration acceleration amplitude to
// form a circular buffer
struct Data_Node{
    double respDisplacement;
    struct Data_Node *next;
};

extern int sample_period;

extern struct Data_Node *sensor_measure_buffer; // Set up for data buffer
extern struct Data_Node *sensor_measure_HEAD;   // Circular buffer head pointer
extern struct Data_Node *sensor_measure_TAIL;   // Circular buffer tail pointer

/*-----ApneaMonitor.h-----*/
extern double breathingDisplacementReference; // Reference threshold for apnea
extern char referenceExists; // '1' if already have reference measurement;
                             // else '0'
extern char mostRecentCondition; // boolean to track most recent breathing state
extern int samplesSinceLastStim; // samples elapsed since latest stimulation

/**
 * @brief      Delay by a specified number of no-operations
 *
 * @param[in]  numNops  how many no-operations to delay
 */
void delay_nops(int numNops);

/**
 * @brief      Delay by a specified duration of milliseconds
 *
 * @param[in]  numMillis  how many milliseconds to delay
 */
void delay_ms(int numMillis);

/**
 * @brief      Delay by a specified duration of (multiples of 50) milliseconds
 *
 * @param[in]  num50Millis  how many multiples of 50 milliseconds to delay
 */
void delay_50ms(int num50Millis);

#ifdef	__cplusplus
}
#endif

#endif	/* GLOBALS_H */

