 /**
 *  @file Globals.h
 *  @author Praveenanurag Dulapalli
 *  @date 2015-11-26
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

#include "Globals.h"

void delay_nops(int numNops) {
    int i;
    for (i = 0; i < numNops; i++) {
        nop();
    }
}

void delay_ms(int numMillis){
    int i;
    for (i = 0; i < numMillis; i++) {
        delay_nops(NOP_PER_MS);
    }
}

void delay_50ms(int num50Millis){
    int i;
    for (i = 0; i < num50Millis; i++) {
        delay_nops(NOP_PER_50_MS);
    }
}