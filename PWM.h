#ifndef __PWM_H
#define __PWM_H
/******************************************************************************
 // *                  PULSE WIDTH MODULATION (PWM)  PERIPHERAL LIBRARY HEADER FILE
 ******************************************************************************
 * FileName:        		pwm.h
 * Dependencies:    	See include below
 * Processor:       		PIC18
 * Compiler:        		MCC18
 * Company:         		Microchip Technology, Inc.
 *
 * Software License Agreement
 * The software supplied herewith by Microchip Technology Incorporated
 * (the ÏCompanyÓ) for its PICmicro∆ Microcontroller is intended and
 * supplied to you, the CompanyÌs customer, for use solely and
 * exclusively on Microchip PICmicro Microcontroller products. The
 * software is owned by the Company and/or its supplier, and is
 * protected under applicable copyright laws. All rights are reserved.
 * Any use in violation of the foregoing restrictions may subject the
 * user to criminal sanctions under applicable laws, as well as to
 * civil liability for the breach of the terms and conditions of this
 * license.
 *
 * THIS SOFTWARE IS PROVIDED IN AN ÏAS ISÓ CONDITION. NO WARRANTIES,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED
 * TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE COMPANY SHALL NOT,
 * IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR
 * CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *****************************************************************************/
 
#include <pconfig.h>

/* There are five library modules, corresponding to register names:
 *  PWM1  (CCPCON1)
 *  PWM2  (CCPCON2)
 *  PWM3  (CCPCON3)
 *  PWM4  (CCPCON4)
 *  PWM5  (CCPCON5)
 *  EPWM1  (ECCPCON1)
 *  Each module is defined only for those devices for which the register
 *  name is defined.
 *  Note that the 'E' prefix indicates enhanced CCP capability (in ECCPCON1,
 *  for example); however, the absence of the 'E' prefix does not imply
 *  lack of enhanced capability.  The usage of the 'E' prefix is indicative 
 *  of the register naming convention in the datasheets, not the
 *  functionality.
 */

 /* For each module, there are three routines: an 'open' routine,
  * a 'SetDC' routine, and a 'close' routine.
  *
  * The 'open' routine
  *   - sets the PWM mode as single output;
  *   - sets the PWM period, as specified by the routine's parameter;
  *   - configures the CCPx port pin for output;
  *   - begins the PWM operation.
  *
  * The 'SetDC' routine sets the duty cycle, as specified by the routine's
  * parameter.
  *
  * The 'close' routine turns off PWM operation and configures the CCPx port
  * pin to input.
  *
  * For devices with enhanced CCP capability, an additional 'SetOutput'
  * routine is provided.  This routine takes two parameters:
  *   - 'output_config' is the output configuration:
  *         single output 
  *         full bridge output foward
  *         half bridge output
  *         full bridge output reverse
  *   - 'pwm_mode' is the PWM mode: 
  *         PxA,PxC active high; PxB,PxD active high
  *         PxA,PxC active high; PxB,PxD active low 
  *         PxA,PxC active low; PxB,PxD active high
  *         PxA,PxC active low; PxB,PxD active low 
  * These parameters are represented by symbolic constants defined below.
  * The 'SetOutput' routines set the output configuration and PWM mode;
  * they also configure the port pins corresponding to the output
  * configuration for output.  Note that unlike the 'open' routines, these
  * routines do not set the period nor begin the PWM operation.
  */

/* Union used to hold the 10-bit duty cycle */
union PWMDC
{
    unsigned int lpwm;
    char bpwm[2];
};


/* ***** Enhanced CCP ***** */
/* These devices have enhanced CCP capability.  For PWM, this means up to
 * four outputs.  The 'SetOutput' routines are defined for those modules
 * with this enhanced functionality.  These routines set the output
 * configuration and the PWM mode, as well as configure the appropriate
 * port pins for output.  Note that the port pins configured are those
 * corresponding to microcontroller mode.
 */
 
 
#if  defined (PWM_V4) || defined (PWM_V5) || defined (PWM_V6) ||\
     defined (EPWM_V7) || defined (PWM_V8) || defined (PWM_V10) || \
	 defined (PWM_V11) || defined (PWM_V12) || defined (PWM_V13) ||\
	 defined (PWM_V14) || defined (PWM_V14_1) || defined (EPWM_V14)\
	 || defined (PWM_V14_3) || defined (PWM_V14_4) || defined (PWM_V14_5) || defined (EPWM_V14_3) ||\
	 defined (EPWM_V14_4) || defined (EPWM_V14_5) || defined (EPWM_V14_1) || defined (EPWM_V14_2) || \
	 defined (PWM_V14_2) || defined (PWM_V15_1) || defined (PWM_V15) \
	 || defined (EPWM_V15_1) || defined (EPWM_V15)

#ifndef USE_OR_MASKS

#define SINGLE_OUT     		0b00111111 /*Single output: P1A modulated; P1B, P1C, P1D assigned as port pins*/
#define FULL_OUT_FWD   		0b01111111 /*Full-bridge output forward: P1D modulated; P1A active; P1B, P1C inactive*/
#define HALF_OUT       		0b10111111 /*Half-bridge output: P1A, P1B modulated with dead-band control; P1C, P1D assigned as port pins*/
#define FULL_OUT_REV   		0b11111111 /*Full-bridge output reverse: P1B modulated; P1C active; P1A, P1D inactive*/

#else

#define SINGLE_OUT     		0b00000000 /*Single output: P1A modulated; P1B, P1C, P1D assigned as port pins*/
#define FULL_OUT_FWD   		0b01000000 /*Full-bridge output forward: P1D modulated; P1A active; P1B, P1C inactive*/
#define HALF_OUT       		0b10000000 /*Half-bridge output: P1A, P1B modulated with dead-band control; P1C, P1D assigned as port pins*/
#define FULL_OUT_REV   		0b11000000 /*Full-bridge output reverse: P1B modulated; P1C active; P1A, P1D inactive*/
#define PWM_OP_MODE_MASK	(~FULL_OUT_REV)	//Mask PWM Output Configuration bits

#endif


#define IS_DUAL_PWM(config) ((config) == HALF_OUT)

#define IS_QUAD_PWM(config) ((config) == FULL_OUT_FWD || \
                             (config) == FULL_OUT_REV)
							 
							 
/* The PWM mode is passed as the second parameter to the
 * 'SetOutput' routines. */
#ifndef USE_OR_MASKS

#define PWM_MODE_1     0b11111100 /* PxA,PxC active high, PxB,PxD active high */
#define PWM_MODE_2     0b11111101 /* PxA,PxC active high, PxB,PxD active low */
#define PWM_MODE_3     0b11111110 /* PxA,PxC active low, PxB,PxD active high */
#define PWM_MODE_4     0b11111111 /* PxA,PxC active low, PxB,PxD active low */

#else

#define PWM_MODE_1     0b00001100 /* PxA,PxC active high, PxB,PxD active high */
#define PWM_MODE_2     0b00001101 /* PxA,PxC active high, PxB,PxD active low */
#define PWM_MODE_3     0b00001110 /* PxA,PxC active low, PxB,PxD active high */
#define PWM_MODE_4     0b00001111 /* PxA,PxC active low, PxB,PxD active low */
#define PWM_MODE_MASK	(~PWM_MODE_4)	//Mask PWM Output Configuration bits

#endif

#endif


#if defined (PWM_V14) || defined (PWM_V14_1) || defined (PWM_V14_3) || defined (PWM_V14_4) 

#define __CONFIG3H 0x300005

#ifndef USE_OR_MASKS

//***************** CCP source - TIMER selection ********************************************
//*************CCP4**************
#define CCP_4_SEL_TMR12		    0b11001111  	//CCP selects TIMER1 for Capture & Compare and TIMER2 for PWM
#define CCP_4_SEL_TMR34		    0b11011111  	//CCP selects TIMER3 for Capture & Compare and TIMER4 for PWM
#define CCP_4_SEL_TMR36		    0b11101111  	//CCP selects TIMER3 for Capture & Compare and TIMER6 for PWM

//*************CCP5**************
#define CCP_5_SEL_TMR12		    0b11001111  	//CCP selects TIMER1 for Capture & Compare and TIMER2 for PWM
#define CCP_5_SEL_TMR54		    0b11011111  	//CCP selects TIMER5 for Capture & Compare and TIMER4 for PWM

//*************CCP6**************
#define CCP_6_SEL_TMR12		    0b11001111  	//CCP selects TIMER1 for Capture & Compare and TIMER2 for PWM
#define CCP_6_SEL_TMR52		    0b11011111  	//CCP selects TIMER5 for Capture & Compare and TIMER2 for PWM

//*************CCP7**************
#define CCP_7_SEL_TMR12		    0b11001111  	//CCP selects TIMER1 for Capture & Compare and TIMER2 for PWM
#define CCP_7_SEL_TMR54		    0b11011111  	//CCP selects TIMER5 for Capture & Compare and TIMER4 for PWM
#define CCP_7_SEL_TMR56		    0b11101111  	//CCP selects TIMER5 for Capture & Compare and TIMER6 for PWM
#define CCP_7_SEL_TMR58		    0b11111111  	//CCP selects TIMER5 for Capture & Compare and TIMER8 for PWM

#if defined (PWM_V14) || defined (PWM_V14_3)
//*************CCP8**************
#define CCP_8_SEL_TMR12		    0b11001111  	//CCP selects TIMER1 for Capture & Compare and TIMER2 for PWM
#if defined (PWM_V14)
#define CCP_8_SEL_TMR74		    0b11011111  	//CCP selects TIMER7 for Capture & Compare and TIMER4 for PWM
#define CCP_8_SEL_TMR76		    0b11101111  	//CCP selects TIMER7 for Capture & Compare and TIMER6 for PWM
#else
#define CCP_8_SEL_TMR54		    0b11011111  	//CCP selects TIMER5 for Capture & Compare and TIMER4 for PWM
#define CCP_8_SEL_TMR56		    0b11101111  	//CCP selects TIMER5 for Capture & Compare and TIMER6 for PWM
#endif
#endif

#if defined (PWM_V14_1) || defined (PWM_V14_4)
//*************CCP8**************
#define CCP_8_SEL_TMR12		    0b11001111  	//CCP selects TIMER1 for Capture & Compare and TIMER2 for PWM
#define CCP_8_SEL_TMR14		    0b11011111  	//CCP selects TIMER1 for Capture & Compare and TIMER4 for PWM
#define CCP_8_SEL_TMR16		    0b11101111  	//CCP selects TIMER1 for Capture & Compare and TIMER6 for PWM
#endif

#if defined (PWM_V14) || defined (PWM_V14_3)
//*************CCP9**************
#define CCP_9_SEL_TMR12		    0b11001111  	//CCP selects TIMER1 for Capture & Compare and TIMER2 for PWM
#if defined (PWM_V14_3)
#define CCP_9_SEL_TMR54		    0b11011111  	//CCP selects TIMER5 for Capture & Compare and TIMER4 for PWM
#else
#define CCP_9_SEL_TMR74		    0b11011111  	//CCP selects TIMER7 for Capture & Compare and TIMER4 for PWM
#endif
//*************CCP10**************
#define CCP_10_SEL_TMR12		 0b11001111  	//CCP selects TIMER1 for Capture & Compare and TIMER2 for PWM
#if defined (PWM_V14_3)
#define CCP_10_SEL_TMR52		 0b11011111  	//CCP selects TIMER5 for Capture & Compare and TIMER4 for PWM
#else
#define CCP_10_SEL_TMR72		 0b11011111  	//CCP selects TIMER7 for Capture & Compare and TIMER2 for PWM
#endif
#endif

#else	//USE_OR_MASKS

//***************** CCP source - TIMER selection ********************************************
//*************CCP4**************
#define CCP_4_SEL_TMR12		    0b00000000  	//CCP selects TIMER1 for Capture & Compare and TIMER2 for PWM
#define CCP_4_SEL_TMR34		    0b00010000  	//CCP selects TIMER3 for Capture & Compare and TIMER4 for PWM
#define CCP_4_SEL_TMR36		    0b00100000  	//CCP selects TIMER3 for Capture & Compare and TIMER6 for PWM
#define CCP_4_SEL_TMR_MASK		(~0b00110000)  	//Maks CCP TIMER Source selection bits

//*************CCP5**************
#define CCP_5_SEL_TMR12		    0b00000000  	//CCP selects TIMER1 for Capture & Compare and TIMER2 for PWM
#define CCP_5_SEL_TMR54		    0b00010000  	//CCP selects TIMER5 for Capture & Compare and TIMER4 for PWM
#define CCP_5_SEL_TMR_MASK		(~0b00010000)  	//Maks CCP TIMER Source selection bits

//*************CCP6**************
#define CCP_6_SEL_TMR12		    0b00000000  	//CCP selects TIMER1 for Capture & Compare and TIMER2 for PWM
#define CCP_6_SEL_TMR52		    0b00010000  	//CCP selects TIMER5 for Capture & Compare and TIMER2 for PWM
#define CCP_6_SEL_TMR_MASK		(~0b00010000)  	//Maks CCP TIMER Source selection bits

//*************CCP7**************
#define CCP_7_SEL_TMR12		    0b00000000  	//CCP selects TIMER1 for Capture & Compare and TIMER2 for PWM
#define CCP_7_SEL_TMR54		    0b00010000  	//CCP selects TIMER5 for Capture & Compare and TIMER4 for PWM
#define CCP_7_SEL_TMR56		    0b00100000  	//CCP selects TIMER5 for Capture & Compare and TIMER6 for PWM
#define CCP_7_SEL_TMR58		    0b00110000  	//CCP selects TIMER5 for Capture & Compare and TIMER8 for PWM
#define CCP_7_SEL_TMR_MASK		(~0b00110000)  	//Maks CCP TIMER Source selection bits

#if defined (PWM_V14) || defined (PWM_V14_3)
//*************CCP8**************
#define CCP_8_SEL_TMR12		    0b00000000  	//CCP selects TIMER1 for Capture & Compare and TIMER2 for PWM
#if defined (PWM_V14)
#define CCP_8_SEL_TMR74		    0b00010000  	//CCP selects TIMER7 for Capture & Compare and TIMER4 for PWM
#define CCP_8_SEL_TMR76		    0b00100000  	//CCP selects TIMER7 for Capture & Compare and TIMER6 for PWM
#else
#define CCP_8_SEL_TMR54		    0b00010000  	//CCP selects TIMER5 for Capture & Compare and TIMER4 for PWM
#define CCP_8_SEL_TMR56		    0b00100000  	//CCP selects TIMER5 for Capture & Compare and TIMER6 for PWM
#endif
#endif
#define CCP_8_SEL_TMR_MASK		(~0b00110000)  	//Maks CCP TIMER Source selection bits

#if defined (PWM_V14_1) || defined (PWM_V14_4)
//*************CCP8**************
#define CCP_8_SEL_TMR12		    0b00000000  	//CCP selects TIMER1 for Capture & Compare and TIMER2 for PWM
#define CCP_8_SEL_TMR14		    0b00010000  	//CCP selects TIMER1 for Capture & Compare and TIMER4 for PWM
#define CCP_8_SEL_TMR16		    0b00100000  	//CCP selects TIMER1 for Capture & Compare and TIMER6 for PWM
#define CCP_8_SEL_TMR_MASK		(~0b00110000)  	//Maks CCP TIMER Source selection bits
#endif

#if defined (PWM_V14) || defined (PWM_V14_3) 
//*************CCP9**************
#define CCP_9_SEL_TMR12		    0b00000000  	//CCP selects TIMER1 for Capture & Compare and TIMER2 for PWM
#if defined (PWM_V14_3)
#define CCP_9_SEL_TMR54		    0b00010000  	//CCP selects TIMER5 for Capture & Compare and TIMER4 for PWM
#else
#define CCP_9_SEL_TMR74		    0b00010000  	//CCP selects TIMER7 for Capture & Compare and TIMER4 for PWM
#endif
#define CCP_9_SEL_TMR_MASK		(~0b00010000)  	//Maks CCP TIMER Source selection bits

//*************CCP10**************
#define CCP_10_SEL_TMR12		 0b00000000  	//CCP selects TIMER1 for Capture & Compare and TIMER2 for PWM
#if defined (PWM_V14_3)
#define CCP_10_SEL_TMR52		 0b00010000  	//CCP selects TIMER5 for Capture & Compare and TIMER4 for PWM
#else
#define CCP_10_SEL_TMR72		 0b00010000  	//CCP selects TIMER7 for Capture & Compare and TIMER2 for PWM
#endif
#define CCP_10_SEL_TMR_MASK		(~0b00010000)  	//Maks CCP TIMER Source selection bits
#endif

#endif	//USE_OR_MASKS
#endif	//main version 


#if defined (EPWM_V14) || defined (EPWM_V14_1) || defined (EPWM_V14_3) || defined (EPWM_V14_4)
#ifndef USE_OR_MASKS
//***************** ECCP source - TIMER selection ********************************************
//*************ECCP1**************
#define ECCP_1_SEL_TMR12		    0b10001111  	//ECCP selects TIMER1 for Capture & Compare and TIMER2 for PWM
#define ECCP_1_SEL_TMR34		    0b10011111  	//ECCP selects TIMER3 for Capture & Compare and TIMER4 for PWM
#define ECCP_1_SEL_TMR36		    0b10101111  	//ECCP selects TIMER3 for Capture & Compare and TIMER6 for PWM
#define ECCP_1_SEL_TMR38		    0b10111111  	//ECCP selects TIMER3 for Capture & Compare and TIMER8 for PWM
#if defined (EPWM_V14)
#define ECCP_1_SEL_TMR310		    0b11001111  	//ECCP selects TIMER3 for Capture & Compare and TIMER10 for PWM
#define ECCP_1_SEL_TMR312		    0b11011111  	//ECCP selects TIMER3 for Capture & Compare and TIMER12 for PWM
#endif

//*************ECCP2**************
#define ECCP_2_SEL_TMR12		    0b10001111  	//ECCP selects TIMER1 for Capture & Compare and TIMER2 for PWM
#define ECCP_2_SEL_TMR34		    0b10011111  	//ECCP selects TIMER3 for Capture & Compare and TIMER4 for PWM
#define ECCP_2_SEL_TMR36		    0b10101111  	//ECCP selects TIMER3 for Capture & Compare and TIMER6 for PWM
#define ECCP_2_SEL_TMR38		    0b10111111  	//ECCP selects TIMER3 for Capture & Compare and TIMER8 for PWM
#if defined (EPWM_V14)
#define ECCP_2_SEL_TMR310		    0b11001111  	//ECCP selects TIMER3 for Capture & Compare and TIMER10 for PWM
#endif

//*************ECCP3**************
#define ECCP_3_SEL_TMR12		    0b11001111  	//ECCP selects TIMER1 for Capture & Compare and TIMER2 for PWM
#define ECCP_3_SEL_TMR34		    0b11011111  	//ECCP selects TIMER3 for Capture & Compare and TIMER4 for PWM
#define ECCP_3_SEL_TMR36		    0b11101111  	//ECCP selects TIMER3 for Capture & Compare and TIMER6 for PWM
#define ECCP_3_SEL_TMR38		    0b11111111  	//ECCP selects TIMER3 for Capture & Compare and TIMER8 for PWM


#else	//USE_OR_MASKS

//***************** ECCP source - TIMER selection ********************************************
//*************ECCP1**************
#define ECCP_1_SEL_TMR12		    0b00000000  	//ECCP selects TIMER1 for Capture & Compare and TIMER2 for PWM
#define ECCP_1_SEL_TMR34		    0b00010000  	//ECCP selects TIMER3 for Capture & Compare and TIMER4 for PWM
#define ECCP_1_SEL_TMR36		    0b00100000  	//ECCP selects TIMER3 for Capture & Compare and TIMER6 for PWM
#define ECCP_1_SEL_TMR38		    0b00110000  	//ECCP selects TIMER3 for Capture & Compare and TIMER8 for PWM
#if defined (EPWM_V14)
#define ECCP_1_SEL_TMR310		    0b01000000  	//ECCP selects TIMER3 for Capture & Compare and TIMER10 for PWM
#define ECCP_1_SEL_TMR312		    0b01010000  	//ECCP selects TIMER3 for Capture & Compare and TIMER12 for PWM
#endif
#define ECCP_1_SEL_TMR_MASK			(~0b01110000)  	//Maks ECCP TIMER Source selection bits

//*************ECCP2**************
#define ECCP_2_SEL_TMR12		    0b00000000  	//ECCP selects TIMER1 for Capture & Compare and TIMER2 for PWM
#define ECCP_2_SEL_TMR34		    0b00010000  	//ECCP selects TIMER3 for Capture & Compare and TIMER4 for PWM
#define ECCP_2_SEL_TMR36		    0b00100000  	//ECCP selects TIMER3 for Capture & Compare and TIMER6 for PWM
#define ECCP_2_SEL_TMR38		    0b00110000  	//ECCP selects TIMER3 for Capture & Compare and TIMER8 for PWM
#if defined (EPWM_V14)
#define ECCP_2_SEL_TMR310		    0b01000000  	//ECCP selects TIMER3 for Capture & Compare and TIMER10 for PWM
#endif
#define ECCP_2_SEL_TMR_MASK			(~0b01110000)  	//Maks ECCP TIMER Source selection bits

//*************ECCP3**************
#define ECCP_3_SEL_TMR12		    0b00000000  	//ECCP selects TIMER1 for Capture & Compare and TIMER2 for PWM
#define ECCP_3_SEL_TMR34		    0b00010000  	//ECCP selects TIMER3 for Capture & Compare and TIMER4 for PWM
#define ECCP_3_SEL_TMR36		    0b00100000  	//ECCP selects TIMER3 for Capture & Compare and TIMER6 for PWM
#define ECCP_3_SEL_TMR38		    0b00110000  	//ECCP selects TIMER3 for Capture & Compare and TIMER8 for PWM
#define ECCP_3_SEL_TMR_MASK			(~0b00110000)  	//Maks ECCP TIMER Source selection bits


#endif	//USE_OR_MASKS
#endif	//main version 


#if defined (PWM_V14_5) || defined (EPWM_V14_5)
#ifndef USE_OR_MASKS
#define ECCP_1_SEL_TMR12		0b11101111  	//ECCP selects TIMER1 for Capture & Compare and TIMER2 for PWM
#define ECCP_1_SEL_TMR32		0b11111111  	//ECCP selects TIMER3 for Capture & Compare and TIMER2 for PWM

#define CCP_2_SEL_TMR12		    0b11101111  	//CCP selects TIMER1 for Capture & Compare and TIMER2 for PWM
#define CCP_2_SEL_TMR32		    0b11111111  	//CCP selects TIMER3 for Capture & Compare and TIMER2 for PWM

#else
#define ECCP_1_SEL_TMR12	    0b00000000  	//ECCP selects TIMER1 for Capture & Compare and TIMER2 for PWM
#define ECCP_1_SEL_TMR32	    0b00010000  	//ECCP selects TIMER3 for Capture & Compare and TIMER2 for PWM
#define ECCP_1_SEL_TMR_MASK		(~0b00010000)  	//Maks ECCP TIMER Source selection bits

#define CCP_2_SEL_TMR12		    0b00000000  	//CCP selects TIMER1 for Capture & Compare and TIMER2 for PWM
#define CCP_2_SEL_TMR32		    0b00010000  	//CCP selects TIMER3 for Capture & Compare and TIMER2 for PWM
#define CCP_2_SEL_TMR_MASK		(~0b00010000)  	//Maks CCP TIMER Source selection bits

#endif
#endif


#if defined (PWM_V14_2) || defined (EPWM_V14_2)
#ifndef USE_OR_MASKS
#define ECCP_1_SEL_TMR12		0b11101111  	//ECCP selects TIMER1 for Capture & Compare and TIMER2 for PWM
#define ECCP_1_SEL_TMR34		0b11111111  	//ECCP selects TIMER3 for Capture & Compare and TIMER4 for PWM

#define CCP_2_SEL_TMR12		    0b11101111  	//CCP selects TIMER1 for Capture & Compare and TIMER2 for PWM
#define CCP_2_SEL_TMR34		    0b11111111  	//CCP selects TIMER3 for Capture & Compare and TIMER4 for PWM

#define CCP_3_SEL_TMR12		    0b11101111  	//CCP selects TIMER1 for Capture & Compare and TIMER2 for PWM
#define CCP_3_SEL_TMR34		    0b11111111  	//CCP selects TIMER3 for Capture & Compare and TIMER4 for PWM

#define CCP_4_SEL_TMR12		    0b11101111  	//CCP selects TIMER1 for Capture & Compare and TIMER2 for PWM
#define CCP_4_SEL_TMR34		    0b11111111  	//CCP selects TIMER3 for Capture & Compare and TIMER4 for PWM

#define CCP_5_SEL_TMR12		    0b11101111  	//CCP selects TIMER1 for Capture & Compare and TIMER2 for PWM
#define CCP_5_SEL_TMR34		    0b11111111  	//CCP selects TIMER5 for Capture & Compare and TIMER4 for PWM

#else
#define ECCP_1_SEL_TMR12	    0b00000000  	//ECCP selects TIMER1 for Capture & Compare and TIMER2 for PWM
#define ECCP_1_SEL_TMR34	    0b00010000  	//ECCP selects TIMER3 for Capture & Compare and TIMER4 for PWM
#define ECCP_1_SEL_TMR_MASK		(~0b00010000)  	//Maks ECCP TIMER Source selection bits

#define CCP_2_SEL_TMR12		    0b00000000  	//CCP selects TIMER1 for Capture & Compare and TIMER2 for PWM
#define CCP_2_SEL_TMR34		    0b00010000  	//CCP selects TIMER3 for Capture & Compare and TIMER4 for PWM
#define CCP_2_SEL_TMR_MASK		(~0b00010000)  	//Maks CCP TIMER Source selection bits

#define CCP_3_SEL_TMR12		    0b00000000  	//CCP selects TIMER1 for Capture & Compare and TIMER2 for PWM
#define CCP_3_SEL_TMR34		    0b00010000  	//CCP selects TIMER3 for Capture & Compare and TIMER4 for PWM
#define CCP_3_SEL_TMR_MASK		(~0b00010000)  	//Maks CCP TIMER Source selection bits

#define CCP_4_SEL_TMR12		    0b00000000  	//CCP selects TIMER1 for Capture & Compare and TIMER2 for PWM
#define CCP_4_SEL_TMR34		    0b00010000  	//CCP selects TIMER3 for Capture & Compare and TIMER4 for PWM
#define CCP_4_SEL_TMR_MASK		(~0b00010000)  	//Maks CCP TIMER Source selection bits

#define CCP_5_SEL_TMR12		    0b00000000  	//CCP selects TIMER1 for Capture & Compare and TIMER2 for PWM
#define CCP_5_SEL_TMR34		    0b00010000  	//CCP selects TIMER5 for Capture & Compare and TIMER4 for PWM
#define CCP_5_SEL_TMR_MASK		(~0b00010000)  	//Maks CCP TIMER Source selection bits
#endif
#endif


#if defined (PWM_V15) || defined (EPWM_V15) || defined (PWM_V15_1) || defined (EPWM_V15_1)
#ifndef USE_OR_MASKS
#define ECCP_1_SEL_TMR12		0b11100111  	//ECCP selects TIMER1 for Capture & Compare and TIMER2 for PWM
#define ECCP_1_SEL_TMR34		0b11101111  	//ECCP selects TIMER3 for Capture & Compare and TIMER4 for PWM
#define ECCP_1_SEL_TMR56		0b11110111  	//ECCP selects TIMER5 for Capture & Compare and TIMER6 for PWM

#define ECCP_2_SEL_TMR12		0b00111111  	//ECCP selects TIMER1 for Capture & Compare and TIMER2 for PWM
#define ECCP_2_SEL_TMR34		0b01111111  	//ECCP selects TIMER3 for Capture & Compare and TIMER4 for PWM
#define ECCP_2_SEL_TMR56		0b10111111  	//ECCP selects TIMER5 for Capture & Compare and TIMER6 for PWM

#define ECCP_3_SEL_TMR12		0b11001111  	//ECCP selects TIMER1 for Capture & Compare and TIMER2 for PWM
#define ECCP_3_SEL_TMR34		0b11011111  	//ECCP selects TIMER3 for Capture & Compare and TIMER4 for PWM
#define ECCP_3_SEL_TMR56		0b11101111  	//ECCP selects TIMER5 for Capture & Compare and TIMER6 for PWM

#define CCP_4_SEL_TMR12			0b11001111  	//CCP selects TIMER1 for Capture & Compare and TIMER2 for PWM
#define CCP_4_SEL_TMR34			0b11011111  	//CCP selects TIMER3 for Capture & Compare and TIMER4 for PWM
#define CCP_4_SEL_TMR56			0b11101111  	//CCP selects TIMER5 for Capture & Compare and TIMER6 for PWM

#define CCP_5_SEL_TMR12			0b00111111  	//CCP selects TIMER1 for Capture & Compare and TIMER2 for PWM
#define CCP_5_SEL_TMR34			0b01111111  	//CCP selects TIMER3 for Capture & Compare and TIMER4 for PWM
#define CCP_5_SEL_TMR56			0b10111111  	//CCP selects TIMER5 for Capture & Compare and TIMER6 for PWM

#else
#define ECCP_1_SEL_TMR12	    0b00000000  	//ECCP selects TIMER1 for Capture & Compare and TIMER2 for PWM
#define ECCP_1_SEL_TMR34	    0b00001000  	//ECCP selects TIMER3 for Capture & Compare and TIMER4 for PWM
#define ECCP_1_SEL_TMR56	    0b00010000  	//ECCP selects TIMER5 for Capture & Compare and TIMER6 for PWM
#define ECCP_1_SEL_TMR_MASK		(~0b00011000)  	//Maks ECCP TIMER Source selection bits

#define ECCP_2_SEL_TMR12	    0b00000000  	//ECCP selects TIMER1 for Capture & Compare and TIMER2 for PWM
#define ECCP_2_SEL_TMR34	    0b01000000  	//ECCP selects TIMER3 for Capture & Compare and TIMER4 for PWM
#define ECCP_2_SEL_TMR56	    0b10000000  	//ECCP selects TIMER5 for Capture & Compare and TIMER6 for PWM
#define ECCP_2_SEL_TMR_MASK		(~0b11000000)  	//Maks ECCP TIMER Source selection bits

#define ECCP_3_SEL_TMR12	    0b00000000  	//ECCP selects TIMER1 for Capture & Compare and TIMER2 for PWM
#define ECCP_3_SEL_TMR34	    0b00010000  	//ECCP selects TIMER3 for Capture & Compare and TIMER4 for PWM
#define ECCP_3_SEL_TMR56	    0b00100000  	//ECCP selects TIMER5 for Capture & Compare and TIMER6 for PWM
#define ECCP_3_SEL_TMR_MASK		(~0b00110000)  	//Maks ECCP TIMER Source selection bits

#define CCP_4_SEL_TMR12	    	0b00000000  	//CCP selects TIMER1 for Capture & Compare and TIMER2 for PWM
#define CCP_4_SEL_TMR34	    	0b00010000  	//CCP selects TIMER3 for Capture & Compare and TIMER4 for PWM
#define CCP_4_SEL_TMR56	    	0b00100000  	//CCP selects TIMER5 for Capture & Compare and TIMER6 for PWM
#define CCP_4_SEL_TMR_MASK		(~0b00110000)  	//Maks CCP TIMER Source selection bits

#define CCP_5_SEL_TMR12	    	0b00000000  	//CCP selects TIMER1 for Capture & Compare and TIMER2 for PWM
#define CCP_5_SEL_TMR34	    	0b01000000  	//CCP selects TIMER3 for Capture & Compare and TIMER4 for PWM
#define CCP_5_SEL_TMR56	    	0b10000000  	//CCP selects TIMER5 for Capture & Compare and TIMER6 for PWM
#define CCP_5_SEL_TMR_MASK		(~0b11000000)  	//Maks CCP TIMER Source selection bits
#endif
#endif

void OpenPWM1 ( char period);
void SetDCPWM1 ( unsigned int duty_cycle);
#if  defined (PWM_V4) || defined (PWM_V5) || defined (PWM_V6) ||\
     defined (EPWM_V7) || defined (PWM_V8) || defined (PWM_V10) || \
	 defined (PWM_V11) || defined (PWM_V12)|| defined (PWM_V13)


void SetOutputPWM1 ( unsigned char output_config, 
                     unsigned char pwm_mode);
#endif
void ClosePWM1 (void);



#if defined (PWM_V2) || defined (PWM_V3) || defined (PWM_V4) || \
    defined (PWM_V5) || defined (PWM_V6) || defined (PWM_V9) ||\
    defined (PWM_V10) || defined (PWM_V11) || defined (PWM_V13)	

void OpenPWM2 ( char period);
void SetDCPWM2( unsigned int duty_cycle);

#if  defined (PWM_V4)
void SetOutputPWM2 ( unsigned char output_config, 
                     unsigned char pwm_mode);
#endif
void ClosePWM2 (void);

#endif



#if  defined (PWM_V3) || defined (PWM_V4) || defined (PWM_V9)

void OpenPWM3 ( char period);
void SetDCPWM3 ( unsigned int duty_cycle);
#if  defined (PWM_V4)
void SetOutputPWM3 ( unsigned char output_config,
                     unsigned char pwm_mode);
#endif
void ClosePWM3 (void);

#endif



#if defined (PWM_V4) || defined (PWM_V9)

void OpenPWM4 ( char period);
void SetDCPWM4 ( unsigned int duty_cycle);
void ClosePWM4 (void);

void OpenPWM5 ( char period);
void SetDCPWM5 ( unsigned int duty_cycle);
void ClosePWM5 (void);

#endif

#if defined (PWM_V14_2) || defined (PWM_V14_5)
void OpenPWM2 ( unsigned char period, unsigned char timer_source );
void SetDCPWM2 ( unsigned int duty_cycle);
void ClosePWM2 (void);
#if defined (PWM_V14_2)
void OpenPWM3 ( unsigned char period, unsigned char timer_source );
void SetDCPWM3 ( unsigned int duty_cycle);
void ClosePWM3 (void);
#endif
#endif

#if defined (PWM_V14) || defined (PWM_V14_1) || defined (PWM_V14_2)\
 || defined (PWM_V14_3) || defined (PWM_V14_4) || defined (PWM_V15) ||defined (PWM_V15_1)

void OpenPWM4 ( unsigned char period, unsigned char timer_source );
void SetDCPWM4 ( unsigned int duty_cycle);
void ClosePWM4 (void);

void OpenPWM5 ( unsigned char period, unsigned char timer_source );
void SetDCPWM5 ( unsigned int duty_cycle);
void ClosePWM5 (void);

#if defined (PWM_V14) || defined (PWM_V14_1) || defined (PWM_V14_3) || defined (PWM_V14_4)
void OpenPWM6 ( unsigned char period, unsigned char timer_source );
void SetDCPWM6 ( unsigned int duty_cycle);
void ClosePWM6 (void);

void OpenPWM7 ( unsigned char period, unsigned char timer_source );
void SetDCPWM7 ( unsigned int duty_cycle);
void ClosePWM7 (void);

void OpenPWM8 ( unsigned char period, unsigned char timer_source );
void SetDCPWM8 ( unsigned int duty_cycle);
void ClosePWM8 (void);

#if defined (PWM_V14) || defined (PWM_V14_3)
void OpenPWM9 ( unsigned char period, unsigned char timer_source );
void SetDCPWM9 ( unsigned int duty_cycle);
void ClosePWM9 (void);

void OpenPWM10 ( unsigned char period, unsigned char timer_source );
void SetDCPWM10 ( unsigned int duty_cycle);
void ClosePWM10 (void);
#endif
#endif

#endif


#if defined (EPWM_V7)

void OpenEPWM1 ( char period);
void SetDCEPWM1 ( unsigned int duty_cycle);
void SetOutputEPWM1 ( unsigned char output_config,
                      unsigned char pwm_mode);
void CloseEPWM1 (void);

#endif

#if defined (EPWM_V14) || defined (EPWM_V14_1) || defined (EPWM_V14_2)\
 || defined (EPWM_V14_3) || defined (EPWM_V14_4) || defined (EPWM_V14_5) || defined (EPWM_V15) || defined (EPWM_V15_1)

void OpenEPWM1( unsigned char period, unsigned char timer_source );
void SetDCEPWM1 ( unsigned int duty_cycle);
void SetOutputEPWM1 ( unsigned char output_config,
                      unsigned char pwm_mode);
void CloseEPWM1 (void);

#if defined (EPWM_V14) || defined (EPWM_V14_1) || defined (EPWM_V14_3) ||\
	defined (EPWM_V14_4) || defined (EPWM_V15) || defined (EPWM_V15_1)
void OpenEPWM2( unsigned char period, unsigned char timer_source );
void SetDCEPWM2 ( unsigned int duty_cycle);
void SetOutputEPWM2 ( unsigned char output_config,
                      unsigned char pwm_mode);
void CloseEPWM2 (void);


void OpenEPWM3( unsigned char period, unsigned char timer_source );
void SetDCEPWM3 ( unsigned int duty_cycle);
void SetOutputEPWM3 ( unsigned char output_config,
                      unsigned char pwm_mode);
void CloseEPWM3 (void);
#endif
#endif


#if defined CC1_IO_V1	
#define PWM1_TRIS	TRISBbits.TRISB3 
#elif defined CC1_IO_V2
#define PWM1_TRIS	TRISCbits.TRISC5 
#elif defined CC8_IO_V1
#define PWM1_TRIS    TRISBbits.TRISB4
#elif defined CC8_IO_V2
#define PWM1_TRIS    TRISDbits.TRISD4
#elif defined CC9_IO_V1
#define PWM1_TRIS    TRISCbits.TRISC2
#else
#define	PWM1_TRIS	TRISCbits.TRISC2 
#endif

#if defined CC8_IO_V1
#define PWM2_TRIS    TRISCbits.TRISC2
#elif defined CC8_IO_V2
#define PWM2_TRIS    TRISCbits.TRISC2
#elif defined CC9_IO_V1
#define PWM2_TRIS    TRISBbits.TRISB3
#else
#define PWM2_TRIS    TRISEbits.TRISE7
#endif

#if defined CC3_IO_V1	
#define PWM3_TRIS	TRISDbits.TRISD1 
#elif defined CC8_IO_V1
#define PWM3_TRIS    TRISCbits.TRISC6
#elif defined CC8_IO_V2
#define PWM3_TRIS    TRISCbits.TRISC6
#elif defined CC9_IO_V1
#define PWM3_TRIS    TRISBbits.TRISB5
#else	
#define PWM3_TRIS	TRISGbits.TRISG0 
#endif

#if defined CC4_IO_V1
#define PWM4_TRIS    TRISDbits.TRISD2
#elif defined CC4_IO_V2
#define PWM4_TRIS    TRISBbits.TRISB4
#elif defined CC8_IO_V1
#define PWM4_TRIS    TRISCbits.TRISC7
#elif defined CC8_IO_V2
#define PWM4_TRIS    TRISCbits.TRISC7
#elif defined CC9_IO_V1
#define PWM4_TRIS    TRISBbits.TRISB0
#else
#define PWM4_TRIS    TRISGbits.TRISG3
#endif

#if defined CC4_IO_V2	
#define PWM5_TRIS    TRISBbits.TRISB5
#elif defined CC8_IO_V1
#define PWM5_TRIS    TRISBbits.TRISB5
#elif defined CC8_IO_V2
#define PWM5_TRIS    TRISBbits.TRISB5
#elif defined CC9_IO_V1
#define PWM5_TRIS    TRISAbits.TRISA4
#else	
#define PWM5_TRIS    TRISGbits.TRISG4
#endif

#if defined CC4_IO_V2	
#define PWM6_TRIS    TRISBbits.TRISB6
#else	
#define PWM6_TRIS    TRISEbits.TRISE6
#endif

#if defined CC4_IO_V2	
#define PWM7_TRIS    TRISBbits.TRISB7
#else	
#define PWM7_TRIS    TRISEbits.TRISE5
#endif

#if defined CC4_IO_V2	
#define PWM8_TRIS    TRISCbits.TRISC1
#else	
#define PWM8_TRIS    TRISEbits.TRISE4
#endif

#if defined CC4_IO_V2	
#define PWM9_TRIS    TRISCbits.TRISC6
#else	
#define PWM9_TRIS    TRISEbits.TRISE3
#endif

#if defined CC4_IO_V2	
#define PWM10_TRIS    TRISCbits.TRISC7
#else	
#define PWM10_TRIS   TRISEbits.TRISE2
#endif

#endif
