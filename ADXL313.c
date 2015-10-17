/*
 * File:   ADXL313.c
 * Author: Praveenanurag Dulapalli
 *
 * Created: 10/02/2015
 * Last Modified: 10/11/2015
 */

#include "ADXL313.h"

/*

#define ADXL313_SPI_4_WIRE          0b0
#define ADXL313_HALF_G_RANGE        0b00
#define ADXL313_MEASUREMENT_ENABLE  0b1
#define ADXL313_NO_SLEEP            0b0
#define ADXL313_LEFT_JUSTIFY        0b1
#define ADXL313_SELF_TEST_OFF       0b0
#define ADXL313_DISABLE_I2C         0b1
#define ADXL313_DEASSERT_LINK       0b0

 */
void initializeADXL313(void){    
   //SOFTRESET = ADXL313_BEGIN_SOFT_RESET;
    
    
    
    //POWERCTLbits.SLEEP = ADXL313_NO_SLEEP;
    //POWERCTLbits.LINK = ADXL313_DEASSERT_LINK;
    //POWERCTLbits.I2C_DISABLE = ADXL313_DISABLE_I2C;
    //POWERCTLbits.MEASURE = ADXL313_MEASUREMENT_MODE;
    
    
    //prepareRegisterControlBits(ADXL313_POWER_CTL);
    
    
    
    //DATAFORMATbits.SELF_TEST = ADXL313_SELF_TEST_OFF;
    //DATAFORMATbits.SPI = ADXL313_SPI_4_WIRE;
    //DATAFORMATbits.RANGE = ADXL313_HALF_G_RANGE;
    //DATAFORMATbits.JUSTIFY = ADXL313_LEFT_JUSTIFY;
    //prepareRegisterControlBits(ADXL313_DATA_FORMAT);
    
    
    
}

/* Power Ctl
    unsigned WAKE_UP:2;
    unsigned SLEEP:1;
    unsigned MEASURE:1;
    unsigned AUTO_SLEEP:1;
    unsigned LINK:1;
    unsigned I2C_DISABLE:1;
    unsigned :1;
 */

/* Data Format
 EXTERN volatile struct {
    unsigned RANGE:2;
    unsigned JUSTIFY:1;
    unsigned FULL_RES:1;
    unsigned :1;
    unsigned INT_INVERT:1;
    unsigned SPI:1;
    unsigned SELF_TEST:1;
} DATAFORMATbits;
*/

/*
void prepareRegisterControlBits(unsigned char whichRegister){
    switch(whichRegister){
        case ADXL313_POWER_CTL:
            POWERCTL = (LOW_BIT << D7)                  | 
                       (POWERCTLbits.I2C_DISABLE << D6) | 
                       (POWERCTLbits.LINK << D5)        | 
                       (POWERCTLbits.AUTO_SLEEP << D4)  |
                       (POWERCTLbits.MEASURE << D3)     |
                       (POWERCTLbits.SLEEP << D2)       |
                       (POWERCTLbits.WAKE_UP << D1);
            break;
        case ADXL313_DATA_FORMAT:
            DATAFORMAT =    (DATAFORMATbits.SELF_TEST << D7) | 
                            (DATAFORMATbits.SPI << D6)       | 
                            (DATAFORMATbits.INT_INVERT << D5)|
                            (LOW_BIT << D4)                  |
                            (DATAFORMATbits.FULL_RES << D3)  |
                            (DATAFORMATbits.JUSTIFY << D2)   |
                            (DATAFORMATbits.RANGE << D1);
            break;
        default:
            break;
    }
}
*/

