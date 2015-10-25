/*
 * File:   ADXL313.c
 * Author: Praveenanurag Dulapalli
 *
 * Created: 10/02/2015
 * Last Modified: 10/19/2015
 */

#include "ADXL313.h"
#include "SPIComLink.h"

void initializeADXL313(void){   
    /*
    //Set 4-wire SPI
    DataFormatReg_ADXL313_bits.SPI = ADXL313_SPI_4_WIRE;
    PowerCTLReg_ADXL313_bits.I2C_DISABLE = ADXL313_DISABLE_I2C;
    
    writeRegisterControlBits(REG_ADDR_ADXL313_DATA_FORMAT, DataFormatReg_ADXL313);
    writeRegisterControlBits(REG_ADDR_ADXL313_POWER_CTL, PowerCTLReg_ADXL313); 
    Delay10TCYx(1);

    
    //Call reset routine
    SoftResetReg_ADXL313 = ADXL313_BEGIN_SOFT_RESET;

    writeRegisterControlBits(REG_ADDR_ADXL313_SOFT_RESET, SoftResetReg_ADXL313);
    Delay10TCYx(1);

    
    //Set in standby mode
    PowerCTLReg_ADXL313_bits.MEASURE = ADXL313_STANDBY_MODE;

    writeRegisterControlBits(REG_ADDR_ADXL313_POWER_CTL, PowerCTLReg_ADXL313);
    Delay10TCYx(1);

    
    //Set 1600 Hz output data rate
    BWRateReg_ADXL313_bits.RATE = ADXL313_DATA_RATE_800_HZ;

    writeRegisterControlBits(REG_ADDR_ADXL313_BW_RATE, BWRateReg_ADXL313);
    Delay10TCYx(1);

    //Disable interrupts
    IntEnableReg_ADXL313 = ADXL313_DISABLE_ALL_INTERRUPTS;

    writeRegisterControlBits(REG_ADDR_ADXL313_INT_ENABLE, IntEnableReg_ADXL313);
    Delay10TCYx(1);

    
    //Data format set to +/- 0.5 g measurement range, right justified with full resolution
    
    DataFormatReg_ADXL313_bits.SELF_TEST = ADXL313_SELF_TEST_OFF;
    DataFormatReg_ADXL313_bits.FULL_RES = ADXL313_USE_FULL_RES;
    DataFormatReg_ADXL313_bits.JUSTIFY = ADXL313_RIGHT_JUSTIFY;
    DataFormatReg_ADXL313_bits.RANGE = ADXL313_HALF_G_RANGE;
    
    writeRegisterControlBits(REG_ADDR_ADXL313_DATA_FORMAT, DataFormatReg_ADXL313);
    Delay10TCYx(1);
    
    
    //Disable self-test, sleep, and auto-sleep mode
    
    PowerCTLReg_ADXL313_bits.AUTO_SLEEP = ADXL313_DISABLE_AUTO_SLEEP;
    PowerCTLReg_ADXL313_bits.LINK = ADXL313_DEASSERT_LINK;
    PowerCTLReg_ADXL313_bits.SLEEP = ADXL313_NO_SLEEP;
    PowerCTLReg_ADXL313_bits.MEASURE = ADXL313_MEASUREMENT_ENABLE;
    
    writeRegisterControlBits(REG_ADDR_ADXL313_POWER_CTL, PowerCTLReg_ADXL313);
    Delay10TCYx(1);
     */
    
    //OLD BACKUP
    //ADXL313 Register Initialization Sequence
    
    SPI_Write(REG_ADDR_ADXL313_DATA_FORMAT, 0x40); //Set 4-wire SPI
    Delay10TCYx(1);

    SPI_Write(REG_ADDR_ADXL313_SOFT_RESET, ADXL313_BEGIN_SOFT_RESET); //Reset routine
    Delay10TCYx(1);

    SPI_Write(REG_ADDR_ADXL313_POWER_CTL, 0x00); //Standby
    Delay10TCYx(1);

    SPI_Write(REG_ADDR_ADXL313_BW_RATE, ADXL313_DATA_RATE_800_HZ); //Set 800 Hz output data rate
    Delay10TCYx(1);

    SPI_Write(REG_ADDR_ADXL313_INT_ENABLE, ADXL313_DISABLE_ALL_INTERRUPTS); //DISABLE_INTERRUPTS
    Delay10TCYx(1);

    SPI_Write(REG_ADDR_ADXL313_DATA_FORMAT, 0x00); //Configure data output
    Delay10TCYx(1);

    SPI_Write(REG_ADDR_ADXL313_POWER_CTL, 0x48); //Disable sleep-related bits
                                                   //Begin measurement
    Delay10TCYx(1);
    
}   

void writeRegisterControlBits(unsigned char regAddr, unsigned char regControlBits){
    updateRegisterControlBits(regAddr);
    SPI_Write(regAddr, regControlBits);
}

void updateRegisterControlBits(unsigned char regAddr){
    switch(regAddr){
        case REG_ADDR_ADXL313_POWER_CTL:
            PowerCTLReg_ADXL313 =   (CLEAR << D7)                                   |
                                    (PowerCTLReg_ADXL313_bits.I2C_DISABLE << D6)    |
                                    (PowerCTLReg_ADXL313_bits.LINK << D5)           |
                                    (PowerCTLReg_ADXL313_bits.AUTO_SLEEP << D4)     |
                                    (PowerCTLReg_ADXL313_bits.MEASURE << D3)        |
                                    (PowerCTLReg_ADXL313_bits.SLEEP << D2)          |
                                    (PowerCTLReg_ADXL313_bits.WAKE_UP << D1);
            break;
        case REG_ADDR_ADXL313_DATA_FORMAT:
            DataFormatReg_ADXL313 = (DataFormatReg_ADXL313_bits.SELF_TEST << D7)    |
                                    (DataFormatReg_ADXL313_bits.SPI << D6)          |
                                    (DataFormatReg_ADXL313_bits.INT_INVERT << D5)   |
                                    (CLEAR << D4)                                   |
                                    (DataFormatReg_ADXL313_bits.FULL_RES << D3)     |
                                    (DataFormatReg_ADXL313_bits.JUSTIFY << D2)      |
                                    (DataFormatReg_ADXL313_bits.RANGE << D1);
            break;
        case REG_ADDR_ADXL313_INT_ENABLE:
            IntEnableReg_ADXL313 =  (IntEnableReg_ADXL313_bits.DATA_READY << D7)    |
                                    (CLEAR << D6)                                   |
                                    (CLEAR << D5)                                   |
                                    (IntEnableReg_ADXL313_bits.ACTIVITY << D4)      |
                                    (IntEnableReg_ADXL313_bits.INACTIVITY << D3)    |
                                    (CLEAR << D2)                                   |
                                    (IntEnableReg_ADXL313_bits.WATERMARK << D1)     |
                                    (IntEnableReg_ADXL313_bits.OVERRUN);
            break;
        case REG_ADDR_ADXL313_BW_RATE:
            BWRateReg_ADXL313 =     (CLEAR << D7)                                   |
                                    (CLEAR << D6)                                   |
                                    (CLEAR << D5)                                   |
                                    (BWRateReg_ADXL313_bits.LOW_POWER << D4)        |
                                    (BWRateReg_ADXL313_bits.RATE << D3);
            break;
    }
}

void readAxisMeasurements(void){
//    SPI_Read(REG_ADDR_ADXL313_DATA_X
}

int bit_Test(unsigned char axisMeasurement, unsigned char expectedSign){
    return 0;
}



