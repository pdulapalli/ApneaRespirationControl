/**
 *  @file ApneaMonitor.c
 *  @author Praveenanurag Dulapalli
 *  @date 2015-11-12
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

#include "ApneaMonitor.h"

//NOTE: Units for acceleration in this file are in milli-G's

double breathingDisplacementReference = 0;
double errorReference = 0;
char lastCondition = 0;
double refCount = 0;
double delayCount = 0;

int checkApneaCondition(void) {
    unsigned int i, current_condition, error_condition;
    struct Data_Node *currentPoint = sensor_measure_buffer;
    current_condition = IS_APNEA;
    error_condition = TRUE;

    if (referenceExists) { // Only check for apnea if we already have reference
        for (i = 0; i < BUFFER_LENGTH; i++) {
             // If any measurement in past 6 seconds exceeds apnea reference
             // threshold then is not an apneic event
            if (currentPoint->respDisplacement >=
                breathingDisplacementReference) {
                current_condition = IS_NORMAL_RESP;
            }

            // If any measurement in past 6 seconds exceeds error reference
            // threshold then system is not in error state
            if (currentPoint->respDisplacement >= errorReference) {
                error_condition = FALSE;
            }
            currentPoint = currentPoint->next;
        }

        // Some actions to perform only if apneic event occurred recently
        if (lastCondition == IS_APNEA) {
            if (error_condition) {
                current_condition = IS_ERROR;
            } else if (current_condition == IS_NORMAL_RESP) {
                // If patient has returned to normal breathing,
                // recalculate apnea reference threshold
                current_condition = RESET_REFERENCE;
            }
        }
        lastCondition = current_condition;
        return current_condition;
    } else {
        lastCondition = IS_NORMAL_RESP;
        return IS_NORMAL_RESP;
    }
}

void addToReferenceCalc(struct Data_Node *dataPoint) {
    double displacement = dataPoint->respDisplacement;

    if (!referenceExists) {
        // Perform RMS calculations
        breathingDisplacementReference += pow(fabs(displacement), 2);
        refCount++;

        if (refCount == APNEA_REFERENCE_DURATION*MEASUREMENT_SAMPLE_RATE) {
            breathingDisplacementReference /= refCount;
            breathingDisplacementReference = sqrt(breathingDisplacementReference);
            errorReference = .95*breathingDisplacementReference; // Determine
                                                                 // error state
                                                                 // threshold
            referenceExists = !referenceExists;
        }
    }
}

void sendStimulus(void) {
    int i;
    double numRepetitions;

    numRepetitions = APNEA_STIMULATION_DURATION;
    numRepetitions /= .02;

    for (i = 0; i < numRepetitions; i++) {
        STIMULUS_PIN = HIGH;
        delay_nops(NOP_PER_300_US);
        STIMULUS_PIN = LOW;
        delay_nops(NOP_PER_19700_US);
    }
}

void delayOneSamplePeriod(void) {
    int i, j, millisToDelay;
    double samplePeriodMillis;
    int numMillis, num50Millis;

    samplePeriodMillis = 1000;
    samplePeriodMillis /= MEASUREMENT_SAMPLE_RATE;

    num50Millis = numMillis = (int) samplePeriodMillis;
    num50Millis /= 50;

    numMillis = numMillis % 50;

    // Delay in increments of 50 ms and then in single ms
    // Reason: adjust for irregularities in clock timing

    for (i = 0; i < num50Millis; i++) {
        delay_50ms(1);
    }

    for (j = 0; i < numMillis; j++) {
        delay_ms(1);
    }
}

void referenceReset(void) {
    referenceExists = FALSE; // Enables beacon to recalculate reference
    refCount = 0;
}



