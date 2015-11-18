#include "ApneaMonitor.h"

//NOTE: Units for acceleration in this file are in milli-G's

double breathingDisplacementReference = 0;
char lastCondition = 0;
double refCount = 0;
double delayCount = 0;
char measurementReady = 1;

int checkApneaCondition(void){
    unsigned int i, current_condition;
    struct Data_Node *currentPoint = sensor_measure_buffer;
    current_condition = IS_APNEA;
    
    if(referenceExists){
        for(i = 0; i < BUFFER_LENGTH; i++){
            if(currentPoint->respDisplacement >= breathingDisplacementReference){
                current_condition = IS_NORMAL_RESP;
            }
            currentPoint = currentPoint->next;
        }
        if(current_condition == IS_APNEA && lastCondition == IS_APNEA){
            current_condition = IS_ERROR;
        } else if(current_condition == IS_NORMAL_RESP && lastCondition == IS_APNEA){
            current_condition = RESET_REFERENCE;
        }
           
        lastCondition = current_condition;
        
        return current_condition;
        
    } else{
        lastCondition = IS_NORMAL_RESP;
        
        return IS_NORMAL_RESP;
    }
}

void addToReferenceCalc(struct Data_Node *dataPoint){
    double displacement = dataPoint->respDisplacement;
    
    if(!referenceExists){
        breathingDisplacementReference += pow(fabs(displacement), 2);
        refCount++;
        
        if(refCount == APNEA_REFERENCE_DURATION*MEASUREMENT_SAMPLE_RATE){
            breathingDisplacementReference /= refCount;
            breathingDisplacementReference = sqrt(breathingDisplacementReference);
            referenceExists = !referenceExists;
        }   
    }
}

int readyToMeasure(void){
    if(!measurementReady && delayCount < MEASUREMENT_STALL_DURATION*MEASUREMENT_SAMPLE_RATE){
        delayCount++;
    } else{
        delayCount = 0;
        measurementReady = TRUE;
    }
    
    return measurementReady;
}


void sendStimulus(void){
    int i;
    double numRepetitions;
    numRepetitions = APNEA_STIMULATION_DURATION;
    numRepetitions /= .02;
    
    for(i = 0; i < numRepetitions; i++){  
        STIMULUS_PIN = HIGH;
        delay_nops(NOP_PER_300_US);
        STIMULUS_PIN = LOW;
        delay_nops(NOP_PER_19700_US);
    }
    
    //measurementReady = FALSE;
}

void delayOneSamplePeriod(void){
    int i, j, millisToDelay;
    double samplePeriodMillis;
    int numMillis, num50Millis;
    
    samplePeriodMillis = 1000;
    samplePeriodMillis /= MEASUREMENT_SAMPLE_RATE;
    
    num50Millis = numMillis = (int) samplePeriodMillis;
    num50Millis /= 50;
    numMillis = numMillis % 50; 
    
    for(i = 0; i < num50Millis; i++){
        delay_50ms(1);
    }
}

void referenceReset(void){
    referenceExists = FALSE;
    refCount = 0;
}



