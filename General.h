/********************************************************************
*
*                
*
*********************************************************************
* FileName: General.h
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
* File Description: This header file contains all general purpose
                    type and constant definition.
*
* Change History:
* Author               Date        Comment
* Chris Tucker      10/18/2010  First version of module code
********************************************************************/

/**
*   @file General.h
*   @brief This file contains generic definitions used within the program.
*   
*/

#ifndef _GENERAL_H
#define _GENERAL_H

#define TRUE  	1                           ///< Allow TRUE to equal 1.
#define FALSE 	0							///< Allow FALSE to equal 0.

#define ENABLE  1                           ///< Allow ENABLE to equal 1.
#define DISABLE 0							///< Allow DISABLE to equal 0.

#define SET  	1                           ///< Allow ENABLE to equal 1.
#define CLEAR	0							///< Allow DISABLE to equal 0.

#define READ  	1                           ///< Allow READ to equal 1.
#define WRITE	0							///< Allow WRITE to equal 0.

typedef unsigned char UINT8_T;				///< UINT8_T means unsigned Char (8-bit)	
typedef unsigned int  UINT16_T;				///< UINT16_T means unsigned Int (16-bit)
typedef unsigned char BOOL;					///< BOOL means unsigned Char (8-bit)

#endif