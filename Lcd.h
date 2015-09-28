/********************************************************************
*
*                
*
*********************************************************************
* FileName:        Lcd.h
* Dependencies:    See INCLUDES section below
* Processor: 	   PIC18F46K22      
* Compiler: 	   C-18       
* Company:         Microchip Technology, Inc.

*
* Software License Agreement:
*
* The software supplied herewith by Microchip Technology Incorporated
* (the "Company") for its PICmicro® Microcontroller is intended and
* supplied to you, the Company's customer, for use solely and
* exclusively on Microchip PICmicro Microcontroller products. The
* software is owned by the Company and/or its supplier, and is
* protected under applicable copyright laws. All rights are reserved.
* Any use in violation of the foregoing restrictions may subject the
* user to criminal sanctions under applicable laws, as well as to
* civil liability for the breach of the terms and conditions of this
* license.
*
* THIS SOFTWARE IS PROVIDED IN AN "AS IS" CONDITION. NO WARRANTIES,
* WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED
* TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
* PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE COMPANY SHALL NOT,
* IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR
* CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
*********************************************************************
* File Description: This file contains service prototype definition
*                   for LCD access on the PicDem 2 Plus demo board.
*
* Change History:
* Author               Date        Comment
* Chris Tucker      10/18/2010  First version of module code
********************************************************************/

/**
*   @file Lcd.h
*   @brief This file contains the function prototypes for LCD.
*   
*/

#ifndef _LCD_H
#define _LCD_H

//*****************************************************************************
// Include and Header files
//*****************************************************************************

#include <p18cxxx.h>
#include <GenericTypeDefs.h>

#include "General.h"

//*****************************************************************************
// Global Knobs
//*****************************************************************************

//*****************************************************************************
// Global Definitions and Equates
//*****************************************************************************

//*****************************************************************************
// Global Variables
//*****************************************************************************

//*****************************************************************************
// Global Constant Strings
//*****************************************************************************

//*****************************************************************************
// Global Variable Strings
//*****************************************************************************

//*****************************************************************************
// Global Function Prototypes
//*****************************************************************************

void LCDInit(void);                             ///< LCD initialization service
void LCDClear(void);                            ///< Screen clearing service
void LCDGoto(UINT8_T Pos,UINT8_T Ln);           ///< Cursor positioning service
void LCDPutChar(UINT8_T Data);                  ///< Outputs ASCII character
void LCDPutByte(UINT8_T Val);                   ///< Outputs binary value
void LCDWriteStr(const rom far char  *Str);     ///< Outputs strings to LCD

#endif

