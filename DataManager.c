#include "DataManager.h"

#define BUFFER_FULL     1
#define BUFFER_EMPTY    2
#define BUFFER_PARTIAL  3

struct Data_Node measureBufferInit[MEASUREMENT_WINDOW_DURATION*MEASUREMENT_SAMPLE_RATE];

unsigned int measureBufferSize = MEASUREMENT_WINDOW_DURATION*MEASUREMENT_SAMPLE_RATE;

struct Data_Node *sensor_measure_buffer = 0; //Pointer to buffer itself
struct Data_Node *sensor_measure_HEAD = 0;   //Points to oldest data
struct Data_Node *sensor_measure_TAIL = 0;   //Points to most recent data

char referenceExists = 0; //'1' if already have reference measurement; '0' otherwise

void initializeCircularBuffer(void){
    AccelData testMeas;
    unsigned int i;
    struct Data_Node *currentNode;

    sensor_measure_buffer = &measureBufferInit[0];
    currentNode = sensor_measure_TAIL = sensor_measure_HEAD = sensor_measure_buffer;

    for(i = 0; i < measureBufferSize; i++){
        currentNode->axisMeasurements.x_axis = 9000+i;
        currentNode->axisMeasurements.y_axis = 9000+i*2;
        currentNode->axisMeasurements.z_axis = 9000+i*3;

        currentNode->next = (currentNode+1);

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

void addData(AccelData *dataToAdd){
    AccelData currData = *dataToAdd;
    if( (checkBufferStatus() == BUFFER_EMPTY) && 
        (sensor_measure_HEAD->axisMeasurements.x_axis == 9000) ){ //first entry
        sensor_measure_HEAD->axisMeasurements = currData;   
    } else{
        if(checkBufferStatus() == BUFFER_FULL){ //Overwrite oldest data
            sensor_measure_HEAD = sensor_measure_HEAD->next;
        } 
        sensor_measure_TAIL = sensor_measure_TAIL->next;
        sensor_measure_TAIL->axisMeasurements = currData;
    }
}

void removeOldestData(unsigned int numElements){
    int counter;
    struct Data_Node *current = sensor_measure_HEAD;

    while(current->next != 0){
        current = current->next;
    }
}