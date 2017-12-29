/**
 * File: ArduinoDataCapture.ino
 * Purpose: capture the PIC18F46K22 measured quantity (e.g. respiration displacement) and print it to Serial monitor
 * Author: Praveenanurag Dulapalli
 * Created: 11/20/2015
 *
 * Copyright 2015 Praveenanurag Dulapalli
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may not
 * use this file except in compliance with the License. You may obtain a copy of
 * the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
 * License for the specific language governing permissions and limitations under
 * the License.
 */

#define MAX_VOLTAGE 5 //in V
#define MAX_DISPLACEMENT 150 //in cGs
#define ANALOG_DATA_CAPTURE_PIN A1
#define SAMPLE_PERIOD_MILLIS 250

unsigned long startTime, currentTime;
long rng;

void setup(){
    Serial.begin(9600);
    randomSeed(analogRead(0)); //Using a random number generator with a seed that is also quite variable (floating pin input)
}

void loop(){
    dataCapture(60);
}

void dataCapture(int numSeconds){
    int i, currentData, numSamples;
    float dataOut;

    dataOut = 0;
    //startTime = millis();

    i = 0;
    numSamples = 1000*numSeconds/SAMPLE_PERIOD_MILLIS;

    //while(millis() - startTime <= numSeconds*1000){
    while(i < numSamples){
        currentData = analogRead(ANALOG_DATA_CAPTURE_PIN);
        //currentData = ;
        //rng = random(1, 1023);
        dataOut += (float) currentData;
        dataOut /= 1023;
        dataOut *= MAX_DISPLACEMENT;
        Serial.println(dataOut);
        delay(SAMPLE_PERIOD_MILLIS);
        i++;
    }

    Serial.println("END");
    Serial.end();

}
