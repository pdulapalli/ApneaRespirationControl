#include "ApneaMonitor.h"

double breathingDisplacementRef = 0;
double refCount = 0;

int isApneaCondition(void){
    unsigned int i;
    struct Data_Node *currentPoint = sensor_measure_buffer;
}

void addToReferenceCalc(struct Data_Node *dataPoint){
    AccelData axisVals = dataPoint->axisMeasurements;
    
    if(!referenceExists){
        breathingDisplacementRef += pow(fabs(computeAmplitude(&axisVals)), 2);
        refCount++;
        
        if(refCount == APNEA_REFERENCE_DURATION*MEASUREMENT_SAMPLE_RATE){
            breathingDisplacementRef /= refCount;
            breathingDisplacementRef = sqrt(breathingDisplacementRef);
            referenceExists = !referenceExists;
        }   
    }
    
}


void sendStimulus(void){
    STIMULUS_PIN = 1;
    delay_nops(NOP_PER_300_US);
    STIMULUS_PIN = 0;
    delay_nops(NOP_PER_19700_US);
}

void delayOneSamplePeriod(void){
    int i, millisToDelay;
    double samplePeriodMillis = 1000;
    
    samplePeriodMillis /= MEASUREMENT_SAMPLE_RATE;
    millisToDelay = (int) floor(samplePeriodMillis);
    
    for(i = 0; i < millisToDelay; i++){
        delay_ms(1);
    }
}


