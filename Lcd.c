/********************************************************************
*
*                
*
*********************************************************************
* FileName:        Lcd.c
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
* File Description: This modules includes all service functions for LCD
*                   operations.
*
* Change History:
* Author               Date        Comment
* Chris Tucker      10/18/2010  First version of module code
********************************************************************/

/**
*   @file Lcd.c
*   @brief This modules includes all service functions for LCD
*          operations.
*   @defgroup LCD	LCD Display
*   
*/

//*****************************************************************************
// Include and Header files
//*****************************************************************************

#include "Lcd.h"

//*****************************************************************************
//                            CONSTANT DEFINITION
//*****************************************************************************

#define NB_LINES    2                             ///< Number of display lines			
#define NB_COL      16                            ///< Number of characters per line		

#define OUTP        0                             ///< Sets I/Os as outputs				
#define INP         1                             ///< Sets I/Os as inputs

#define TimeOut_Max	1000						  ///< Set counter number before WaitLCD() Timeout
// Set to 300 to Fault

#define LCD_PWR     LATDbits.LATD7                ///< LCD ON/OFF line					@hideinitializer
#define LCD_EN      LATDbits.LATD6                ///< LCD enable line					@hideinitializer
#define LCD_RW      LATDbits.LATD5                ///< LCD read/write line				@hideinitializer
#define LCD_RS      LATDbits.LATD4                ///< LCD register select line			@hideinitializer
#define LCD_DAT0    LATDbits.LATD0                ///< Data bit 0						@hideinitializer
#define LCD_DAT1    LATDbits.LATD1                ///< Data bit 1						@hideinitializer
#define LCD_DAT2    LATDbits.LATD2                ///< Data bit 2						@hideinitializer
#define LCD_DAT3    LATDbits.LATD3                ///< Data bit 3						@hideinitializer

#define LCD_PWR_DIR TRISDbits.TRISD7             ///< Direction bit for the power line	@hideinitializer
#define LCD_EN_DIR  TRISDbits.TRISD6             ///< Direction for EN control line		@hideinitializer
#define LCD_RW_DIR  TRISDbits.TRISD5             ///< Direction for RW control line		@hideinitializer
#define LCD_RS_DIR  TRISDbits.TRISD6             ///< Direction for RS control line		@hideinitializer
#define LCD_D0_DIR  TRISDbits.TRISD0             ///< Direction for data line 0			@hideinitializer
#define LCD_D1_DIR  TRISDbits.TRISD1             ///< Direction for data line 1			@hideinitializer
#define LCD_D2_DIR  TRISDbits.TRISD2             ///< Direction for data line 2			@hideinitializer
#define LCD_D3_DIR  TRISDbits.TRISD3             ///< Direction for data line 3			@hideinitializer

//*****************************************************************************
//                                SUPPORT MACROS
//*****************************************************************************

#define LCD_ON()    LCD_PWR = ENABLE             ///< Turns the display on			@hideinitializer
#define LCD_OFF()   LCD_PWR = DISABLE            ///< Turns the display off			@hideinitializer

//*****************************************************************************
//                               SUPPORT FUNCTIONS
//*****************************************************************************

/********************************************************************
* Function:         ReadByte
* 
* PreCondition: 	None
*
* Side Effects: 	None
*/
/**
* @ingroup  		LCD
*
* @brief    		This function is called to wait for and return the LCD status
*                  	byte.
*
* @result			{Res}	*[Status] USED in WaitLCD() Function
*
* @note    			This routine is meant to be used from within this module only.
*/
/*******************************************************************/

UINT8_T ReadByte(void)
{
  UINT8_T 	Dat,                              // Local buffer for data from LCD
        	Res;                              // Buffer for return value

  LCD_D0_DIR  = INP;                          // LCD data 0 as input
  LCD_D1_DIR  = INP;                          // LCD data 1 as input
  LCD_D2_DIR  = INP;                          // LCD data 2 as input
  LCD_D3_DIR  = INP;                          // LCD data 3 as input

  LCD_EN = ENABLE;                            // Force high to let LCD set the data
  Nop();                                 	  // Small delay
  Nop();
  Dat = PORTD;                                // Read The first nibble
  LCD_EN = DISABLE;                           // LCD now in receive mode
  Res = Dat << 4;                             // Set high nibble

  LCD_EN = ENABLE;                           // Force high to let LCD set the data
  Nop();                                 	  // Small delay
  Nop();
  Dat = PORTD;                                // Read The second nibble
  LCD_EN = DISABLE;                           // LCD now in receive mode
  Dat &= 0x0F;                                // Only the lowest bits matters
  Res |= Dat;                                 // Combine low nibble

  LCD_D0_DIR  = OUTP;                         // LCD data 0 as output
  LCD_D1_DIR  = OUTP;                         // LCD data 1 as output
  LCD_D2_DIR  = OUTP;                         // LCD data 2 as output
  LCD_D3_DIR  = OUTP;                         // LCD data 3 as output

  return(Res);                                // Return value
}

/********************************************************************
* Function:         WaitLCD
* 
* PreCondition: 	None
*
* Side Effects: 	None
*/
/**
* @ingroup  		LCD
*
* @brief         	This function is called to wait until the LCD has finished
*                  	working and is available for further writing.
*
* @note    			This routine is meant to be used from within this module only.
*/
/*******************************************************************/

void WaitLCD(void)
{
  	UINT8_T Status;                 		// Local buffer for LCD status
	UINT16_T TimeOut_Counter = 0;

  	LCD_RS = CLEAR;                 		// Let the LCD know it's getting a command
  	LCD_RW = READ;                  		// Specify a read command
  do
  {
    Status = ReadByte();            		// Get LCD state
	if (TimeOut_Counter == TimeOut_Max)		// WaitLCD Timeout Error
	{
		do{	LATBbits.LATB3 = LATBbits.LATB2 = LATBbits.LATB1 = ENABLE;	}while(1);				
	}			
	TimeOut_Counter++;	
  } while (Status & 0x80);          // If bit 7 high => LCD busy
  	LCD_RW = WRITE;                 // LCD is now in read mode (MCU in write mode)
	ClrWdt();						// Precautionary Clear of Watch DOG Timer
	TimeOut_Counter = 0;
}

/********************************************************************
* Function:         WriteNibble
* 
* PreCondition: 	None
* Side Effects: 	None
*/
/**
* @ingroup  		LCD
*
* @brief         	This function writes the specified nibble to the LCD and
*                  	notifies the (LCD) controller whether it has to interpret
*                  	the nibble as data or command.
*
* @param	        Cmd		This flag specifies whether the data to be written to
*                   		the LCD is a command or data to be displayed.
*
* @param	        Dat		Actual data or command to be written to the LCD controller.
*
* @note    			This routine is meant to be used from within this module only.
*/
/*******************************************************************/

void WriteNibble(UINT8_T Cmd,UINT8_T Dat)
{
  UINT8_T buf;

  if (Cmd)                                          // If Command To be written
    LCD_RS = CLEAR;
  else                                         // Otherwise we are writing data
    LCD_RS = SET;    			  // Set register select according to specified
  LCD_RW = WRITE;                                   // Set write mode
  LCD_EN = ENABLE;                                 	// Disable LCD

  LCD_DAT0 = LCD_DAT1 = LCD_DAT2 = LCD_DAT3 = CLEAR;    // Clear the data lines
  Nop();                                       			// Small delay
  Nop();

  buf =LATD;                                      	// Getting the high nibble
  buf &= 0xF0;                                      // Clear the low nibble
  LATD = buf | (Dat & 0x0F);          				// Combine & write back to the data lines
  Nop();                         					// Give the data a small delay to settle
  Nop();

  LCD_EN = DISABLE;                            			// Enable LCD => The data is taken now
}

/********************************************************************
* Function:         WriteByte
* 
* PreCondition: 	None
*                                                                           
* Input:        	Cmd, Dat
*
* Output:     		None
*
* Side Effects: 	None
*/
/**
* @ingroup  		LCD
*
* @brief          	This function writes the specified Byte to the LCD and
*                   notifies the (LCD) controller whether it has to interpret
*                   the Byte as data or command. 
*
* @param	        Cmd		This flag specifies whether the data to be written to
*                   		the LCD is a command or data to be displayed.
*
* @param	        Dat		Actual data or command to be written to the LCD controller.
*
* @note    			This routine is meant to be used from within this module only.
*/
/*******************************************************************/ 

void WriteByte(UINT8_T Cmd,UINT8_T Dat)
{
  WriteNibble(Cmd,Dat >> 4);            // Output the high nibble to the LCD
  WriteNibble(Cmd,Dat);                 // Now send the low nibble
}

/********************************************************************
* Function:         LCDInit
* 
* PreCondition: 	None
*
* Side Effects: 	None
*/
/**
* @ingroup  		LCD
*
* @brief          	This routine is called once at start up to initialize the
*                   MCU hardware for proper LCD operation.
*
* @note    			Should be called at system start up only.
*/                                                                          
/*******************************************************************/

void LCDInit(void)
{
  LCD_PWR_DIR = OUTP;             // Power line as output
  LCD_EN_DIR  = OUTP;             // LCD enable as output
  LCD_RW_DIR  = OUTP;             // LCD R/W as output
  LCD_RS_DIR  = OUTP;             // LCD register select as output
  LCD_D0_DIR  = OUTP;             // LCD data 0 as output
  LCD_D1_DIR  = OUTP;             // LCD data 1 as output
  LCD_D2_DIR  = OUTP;             // LCD data 2 as output
  LCD_D3_DIR  = OUTP;             // LCD data 3 as output

  LCD_OFF();                      // Peace of mind only!
  LCD_ON();                       // Turns the LCD display on
  LCD_RS = CLEAR;                 // Set LCD in command mode
  LCD_RW = WRITE;                 // LCD receives data on bus => write mode
  LCD_EN = DISABLE;               // LCD enable data receive (LCD reads whatever is on the bus
  LCD_EN = ENABLE;                // Now LCD sets data when requested

  WaitLCD();
  WriteNibble(TRUE,0x02);
  WaitLCD();
  WriteNibble(TRUE,0x02);
  WaitLCD();
  WriteNibble(TRUE,0x08);
  WaitLCD();
  WriteNibble(TRUE,0x00);
  WaitLCD();
  WriteNibble(TRUE,0x0C);
  WaitLCD();
  WriteNibble(TRUE,0x00);
  WaitLCD();
  WriteNibble(TRUE,0x01);
  WaitLCD();
  WriteNibble(TRUE,0x00);
  WaitLCD();
  WriteNibble(TRUE,0x02);
  WaitLCD();
  WriteNibble(TRUE,0x04);
  WaitLCD();
  WriteNibble(TRUE,0x0E);
  WaitLCD();

  LCDClear();						// Clear LCD display
  LCDGoto(0,0);  					// Go to first row, first column
  LCD_ON();                         // Turns the LCD display on
}

/********************************************************************
* Function:         LCDClear
* 
* PreCondition: 	None
*
* Side Effects: 	None
*/
/**
* @ingroup  		LCD
*
* @brief         	This function is called to wipe the LCD display out.
*
* @note    			None.
*/  
/*******************************************************************/

void LCDClear(void)
{
  WriteByte(TRUE,0x01);                       // Send clear display command
  WaitLCD();                                  // Wait until command is finished
}

/********************************************************************
* Function:         LCDGoto
* 
* PreCondition: 	None
*
* Side Effects: 	None
*/
/**
* @ingroup  		LCD
*
* @brief          	This function positions the cursor at the specified Line
*                   and column.
*
* @param	        Pos		Column (0 to 15) the cursor should be positioned at.
*
* @param	        Ln		Line (0 or 1) the cursor should be positioned at.
*
* @note    			0 <= Pos <= 15               
* @note				0 <= Ln <= 1
*/                                                                    
/*******************************************************************/

void LCDGoto(UINT8_T Pos,UINT8_T Ln)
{
  if ((Ln > (NB_LINES-1)) || (Pos > (NB_COL-1))) 			 // If incorrect line or column
    return;                                                  // Just do nothing

  WriteByte(TRUE,(Ln == 1) ? (0xC0 | Pos) : (0x80 | Pos));   // LCD_Goto command
  WaitLCD();                                      			 // Wait for the LCD to finish
}

/********************************************************************
* Function:         LCDPutChar
* 
* PreCondition: 	None
*
* Side Effects: 	None
*/
/**
* @ingroup  		LCD
*
* @brief          	This function displays the specified ASCII character at
*                   current position on the LCD
*
* @param	        Data		ASCII data character to be displayed.
*
* @note    			None.
*/ 
/*******************************************************************/

void LCDPutChar(UINT8_T Data)
{
  WriteByte(FALSE,Data);              // Go output the character to the display
  WaitLCD();                          // Wait until it's finished
}

/********************************************************************
* Function:         LCDPutByte
* 
* PreCondition: 	None
*
* Side Effects: 	None
*/
/**
* @ingroup  		LCD
*
* @brief          	This function displays the specified binary value at
*                   current position on the LCD. It converts the binary
*                   value into displayable ASCII characters.
*
* @param	        Val		Binary data byte to be displayed
*
* @note    			In the present configuration, this routine displays a
*                   2-digit value, by prefilling with '0' any value lower
*                   than 10.
*/
/*******************************************************************/

void LCDPutByte(UINT8_T Val)
{
  LCDPutChar(Val/10+'0');                   // Output the high digit
  LCDPutChar(Val % 10+'0');                 // Output low
}

/********************************************************************
* Function:         LCDWriteStr
* 
* PreCondition: 	None
*
* Input:        	None
*
* Output:     		None
*
* Side Effects: 	None
*/
/**
* @ingroup  		LCD
*
* @brief          	This function displays the specified string starting from
*                   current position on the LCD.
*
* @param	        Str		IF 0; Terminated string to be displayed.
*
* @note    			None
*/
/*******************************************************************/

void LCDWriteStr(const rom far char  *Str)
{
  UINT8_T i = 0;                                     // Char index buffer

  while (Str[i])                                   // While string not finished
    LCDPutChar(Str[i++]);                          // Go display current char
}

