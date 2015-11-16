#include "PWMOut.h"

void initializePWM(int prescaleFactor){
    switch(prescaleFactor){
        case 1:
            OpenTimer2(TIMER_INT_OFF & T2_PS_1_1);
            break;
        case 4:
            OpenTimer2(TIMER_INT_OFF & T2_PS_1_4);
            break;
        case 16:
            OpenTimer2(TIMER_INT_OFF & T2_PS_1_16);
            break;
    }
    //PWM period = [(PR2) + 1] • 4 • TOSC • (TMR2 prescale value)
    //OpenPWM1(0xF9); //2 kHz
    
}

void writePWM(double valueToWrite){
    /*
    int DutyCycle,i , countup;
    DutyCycle = i = 0;
    countup = 1; //our flag to set up/down dutycycle
    
    while(1) //infinite loop
    {
        if(countup == 1)
        {
            SetDCPWM1(DutyCycle); //Change duty cycle
            DutyCycle++;
            if(DutyCycle == 1024)
                countup = 0;
        }
        else
        {
            SetDCPWM1(DutyCycle); //Change duty cycle
            DutyCycle--;
            if(DutyCycle == 0)
                countup = 1;
        }
        Delay10KTCYx(1);
    }
     */
}
