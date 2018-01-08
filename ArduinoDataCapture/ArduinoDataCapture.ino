/**
*  @file ArduinoDataCapture.ino
*  @author Praveenanurag Dulapalli
*  @date 2015-11-20
*  @brief Captures the PIC18F46K22 measured quantity (e.g. respiration
*         displacement) and prints it to Serial monitor
*  @copyright Copyright 2015 Praveenanurag Dulapalli
*
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

#define MAX_VOLTAGE 5 //in Volts
#define MAX_DISPLACEMENT 150 //in cGs
#define ANALOG_DATA_CAPTURE_PIN A1
#define SAMPLE_PERIOD_MILLIS 250

unsigned long startTime, currentTime;
long rng;

void setup(){
    Serial.begin(9600);
    randomSeed(analogRead(0)); // Using a random number generator with a seed
                               // that also varies (floating ADC pin value)
}

void loop(){
    dataCapture(60);
}

/**
 * @brief Obtain measurements from PIC18F46K22 microcontroller and print them to
 *        Serial monitor
 *
 * @param numSeconds Duration (in seconds) to capture and display received data
 */

void dataCapture(int numSeconds){
    int i, currentData, numSamples;
    float dataOut;

    dataOut = i = 0;
    numSamples = 1000*numSeconds/SAMPLE_PERIOD_MILLIS;

    while(i < numSamples){
        currentData = analogRead(ANALOG_DATA_CAPTURE_PIN);

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