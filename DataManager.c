#include "DataManager.h"

#define BUFFER_FULL     1
#define BUFFER_EMPTY    2
#define BUFFER_PARTIAL  3

struct Data_Node measureBufferInit[MEASUREMENT_WINDOW_DURATION*MEASUREMENT_SAMPLE_RATE];

unsigned int measureBufferSize = MEASUREMENT_WINDOW_DURATION*MEASUREMENT_SAMPLE_RATE;

struct Data_Node *sensor_measure_buffer; //Pointer to buffer itself
struct Data_Node *sensor_measure_HEAD;   //Points to oldest data
struct Data_Node *sensor_measure_TAIL;   //Points to most recent data

char referenceExists = 0; //'1' if already have reference measurement; '0' otherwise

void initializeCircularBuffer(void){
    int i;
    struct Data_Node *currentNode;

    sensor_measure_buffer = &measureBufferInit[0];
    currentNode = sensor_measure_TAIL = sensor_measure_HEAD = sensor_measure_buffer;

    for(i = 0; i < measureBufferSize; i++){
        currentNode->respDisplacement = 6000+i;
        if(i == measureBufferSize - 1){
            currentNode->next = sensor_measure_buffer;
        } else{
            currentNode->next = (currentNode+1);
        }
        currentNode++;
    }
}

int checkBufferStatus(void){
    if(sensor_measure_TAIL->next == sensor_measure_HEAD){
       return BUFFER_FULL;
    } else if(sensor_measure_HEAD == sensor_measure_TAIL){
        return BUFFER_EMPTY;
    } else{
        return BUFFER_PARTIAL;
    }
}

struct Data_Node *addDataAccel(double dataToAdd){
    int q;
    if( (checkBufferStatus() == BUFFER_EMPTY) && 
        (sensor_measure_HEAD->respDisplacement == 6000) ){ //first entry of all time
        sensor_measure_HEAD->respDisplacement = dataToAdd;   
    } else{
        if(checkBufferStatus() == BUFFER_FULL){ //Overwrite oldest data
            sensor_measure_HEAD = sensor_measure_HEAD->next;
        } 
        sensor_measure_TAIL = sensor_measure_TAIL->next;
        sensor_measure_TAIL->respDisplacement = dataToAdd;
        q = 0; 
    }
    
    return sensor_measure_TAIL;
}

void addDataTest(double dataToAdd){
    if( (checkBufferStatus() == BUFFER_EMPTY) && 
        (sensor_measure_HEAD->respDisplacement == 9000) ){ //first entry of all time
        sensor_measure_HEAD->respDisplacement = dataToAdd;   
    } else{
        if(checkBufferStatus() == BUFFER_FULL){ //Overwrite oldest data
            sensor_measure_HEAD = sensor_measure_HEAD->next;
        } 
        sensor_measure_TAIL = sensor_measure_TAIL->next;
        sensor_measure_TAIL->respDisplacement = dataToAdd;
    }
}

void removeOldestData(unsigned int numElements){
    int counter;
    struct Data_Node *current = sensor_measure_HEAD;

    while(current->next != 0){
        current = current->next;
    }
}