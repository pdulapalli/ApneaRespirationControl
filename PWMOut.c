#include "PWMOut.h"

void initializePWM(int prescaleFactor, double PWMFreq, double clockSpeed){
    double PR2val, clockPeriod, PWMPeriod;
    int PR2bitVal;

    //Enable PWM ports
    TRISCbits.TRISC2 = OUTPUT;
    LATCbits.LATC2 = LOW;
    clockPeriod = 1/clockSpeed;
    PWMPeriod = 1/PWMFreq;

    //PWM period = [(PR2) + 1] • 4 • TOSC • (TMR2 prescale value)
    PR2val = PWMPeriod;
    PR2val /= 4*clockPeriod*prescaleFactor;
    PR2val--;

    PR2bitVal = (int) PR2val;
    PR2bitVal = PR2bitVal & 0xFF;

    PR2 = PR2bitVal;

    T2CON = 0b00000111 ;
     
    /*
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
    }*/
}

void writePWM(int dutyCycleBits){
    int CCPR1Lval, CCP1CONval;

    //Determine bit settings for CCP registers
    CCPR1Lval = (dutyCycleBits & 0x3FC) >> 2;
    CCP1CONval = (dutyCycleBits & 0x03) << 4;

    //Write appropriate values to CCP registers
    CCPR1L = CCPR1Lval;
    CCP1CON = (CCP1CONval & 0x30) | 0xC;
    
    CCPR1Lval = 0;
}

void closePWM(void){
    LATCbits.LATC2 = LOW;
    TRISCbits.TRISC2 = INPUT;
    T2CON = 0x00;
    CCPR1L = 0x00;
    CCP1CON = 0x00;
}

int convertAccelDataToDutyCycle(double myValue, double maxVal, int prescaleFactor, double PWMFreq, double clockSpeed){
    double dutyTemp, clockPeriod, PWMPeriod;
    int dataOut;

    clockPeriod = 1/clockSpeed;
    PWMPeriod = 1/PWMFreq;

    dutyTemp = floor((fabs(myValue)));
    dutyTemp /= maxVal;
    dutyTemp *= PWMPeriod;
    dutyTemp /= clockPeriod*prescaleFactor;

    dataOut = (int) dutyTemp;
    dataOut = dataOut & 0x3FF;

    return dataOut;
}
