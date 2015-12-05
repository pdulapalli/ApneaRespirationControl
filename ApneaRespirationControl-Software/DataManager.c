/*
 * File:   DataManager.c
 * Author: Praveenanurag Dulapalli
 *
 * Created: 09/27/2015
 * Last Modified: 11/11/2015
 */

#include "DataManager.h"

//Values designating buffer status
#define BUFFER_FULL     1
#define BUFFER_EMPTY    2
#define BUFFER_PARTIAL  3

//This is the circular buffer declared in memory as an array.
struct Data_Node measureBufferInit[MEASUREMENT_WINDOW_DURATION*MEASUREMENT_SAMPLE_RATE];

//The length of the buffer is determined by the number of samples i.e. duration*rate
unsigned int measureBufferSize = MEASUREMENT_WINDOW_DURATION*MEASUREMENT_SAMPLE_RATE;

struct Data_Node *sensor_measure_buffer; //Pointer to buffer itself
struct Data_Node *sensor_measure_HEAD;   //Points to oldest data
struct Data_Node *sensor_measure_TAIL;   //Points to most recent data

char referenceExists = 0; //'1' if already have reference measurement; '0' otherwise

void initializeCircularBuffer(void){
    int i; //Counter
    struct Data_Node *currentNode; //Pointer to current node in iteration

    sensor_measure_buffer = &measureBufferInit[0];
    currentNode = sensor_measure_TAIL = sensor_measure_HEAD = sensor_measure_buffer;

    for(i = 0; i < measureBufferSize; i++){
        currentNode->respDisplacement = 6000+i;
        if(i == measureBufferSize - 1){ //Last element of buffer in sequential memory (i.e. viewed as an array)
            currentNode->next = sensor_measure_buffer; //The last memory element in buffer will point to
                                                       //the very first memory element of the buffer.
                                                       //This is precisely what makes the buffer "circular"
        } else{
            currentNode->next = (currentNode+1);    //Incrementor
        }
        currentNode++;
    }
}

int checkBufferStatus(void){
    int bufferStatus; //The condition of how filled the buffer is

    if(sensor_measure_TAIL->next == sensor_measure_HEAD){
       //If most recent piece of meaningful data is followed immediately by oldest data, then buffer is full
       bufferStatus = BUFFER_FULL;
    } else if(sensor_measure_HEAD == sensor_measure_TAIL){
        //If start and end of meaningful data are in the same location, then buffer is empty
        bufferStatus = BUFFER_EMPTY;
    } else{
        //If the buffer isn't completely full or empty, return an intermediate value
        bufferStatus = BUFFER_PARTIAL;
    }

    return bufferStatus;
}

struct Data_Node *addDataAccel(double dataToAdd){
    if( (checkBufferStatus() == BUFFER_EMPTY) &&
        (sensor_measure_HEAD->respDisplacement == 6000) ){ //First entry of all time
        sensor_measure_HEAD->respDisplacement = dataToAdd;
    } else{
        if(checkBufferStatus() == BUFFER_FULL){ //Overwrite oldest data
            sensor_measure_HEAD = sensor_measure_HEAD->next; //If buffer is full, have to increment
                                                             //head to next position as well.
                                                             //Ensures the tail/head never collide (a la Snake game)
        }
        sensor_measure_TAIL = sensor_measure_TAIL->next;    //Increment tail to next position
        sensor_measure_TAIL->respDisplacement = dataToAdd;  //Store the data in the new tail
    }

    return sensor_measure_TAIL;
}