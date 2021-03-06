#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=mkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=cof
DEBUGGABLE_SUFFIX=cof
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/ApneaRespirationControl-Software.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=cof
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/ApneaRespirationControl-Software.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=/Users/pdulapalli/Documents/Duke/Fall_2015/BME_464/Project/Apnea_Respiration_Control/ApneaRespirationControl-Software/Lcd.c /Users/pdulapalli/Documents/Duke/Fall_2015/BME_464/Project/Apnea_Respiration_Control/ApneaRespirationControl-Software/DataManager.c /Users/pdulapalli/Documents/Duke/Fall_2015/BME_464/Project/Apnea_Respiration_Control/ApneaRespirationControl-Software/SPIComLink.c /Users/pdulapalli/Documents/Duke/Fall_2015/BME_464/Project/Apnea_Respiration_Control/ApneaRespirationControl-Software/main.c /Users/pdulapalli/Documents/Duke/Fall_2015/BME_464/Project/Apnea_Respiration_Control/ApneaRespirationControl-Software/ADXL313.c /Users/pdulapalli/Documents/Duke/Fall_2015/BME_464/Project/Apnea_Respiration_Control/ApneaRespirationControl-Software/ApneaMonitor.c /Users/pdulapalli/Documents/Duke/Fall_2015/BME_464/Project/Apnea_Respiration_Control/ApneaRespirationControl-Software/Globals.c /Users/pdulapalli/Documents/Duke/Fall_2015/BME_464/Project/Apnea_Respiration_Control/ApneaRespirationControl-Software/AuxLCD.c /Users/pdulapalli/Documents/Duke/Fall_2015/BME_464/Project/Apnea_Respiration_Control/ApneaRespirationControl-Software/PWMOut.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/591047608/Lcd.o ${OBJECTDIR}/_ext/591047608/DataManager.o ${OBJECTDIR}/_ext/591047608/SPIComLink.o ${OBJECTDIR}/_ext/591047608/main.o ${OBJECTDIR}/_ext/591047608/ADXL313.o ${OBJECTDIR}/_ext/591047608/ApneaMonitor.o ${OBJECTDIR}/_ext/591047608/Globals.o ${OBJECTDIR}/_ext/591047608/AuxLCD.o ${OBJECTDIR}/_ext/591047608/PWMOut.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/591047608/Lcd.o.d ${OBJECTDIR}/_ext/591047608/DataManager.o.d ${OBJECTDIR}/_ext/591047608/SPIComLink.o.d ${OBJECTDIR}/_ext/591047608/main.o.d ${OBJECTDIR}/_ext/591047608/ADXL313.o.d ${OBJECTDIR}/_ext/591047608/ApneaMonitor.o.d ${OBJECTDIR}/_ext/591047608/Globals.o.d ${OBJECTDIR}/_ext/591047608/AuxLCD.o.d ${OBJECTDIR}/_ext/591047608/PWMOut.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/591047608/Lcd.o ${OBJECTDIR}/_ext/591047608/DataManager.o ${OBJECTDIR}/_ext/591047608/SPIComLink.o ${OBJECTDIR}/_ext/591047608/main.o ${OBJECTDIR}/_ext/591047608/ADXL313.o ${OBJECTDIR}/_ext/591047608/ApneaMonitor.o ${OBJECTDIR}/_ext/591047608/Globals.o ${OBJECTDIR}/_ext/591047608/AuxLCD.o ${OBJECTDIR}/_ext/591047608/PWMOut.o

# Source Files
SOURCEFILES=/Users/pdulapalli/Documents/Duke/Fall_2015/BME_464/Project/Apnea_Respiration_Control/ApneaRespirationControl-Software/Lcd.c /Users/pdulapalli/Documents/Duke/Fall_2015/BME_464/Project/Apnea_Respiration_Control/ApneaRespirationControl-Software/DataManager.c /Users/pdulapalli/Documents/Duke/Fall_2015/BME_464/Project/Apnea_Respiration_Control/ApneaRespirationControl-Software/SPIComLink.c /Users/pdulapalli/Documents/Duke/Fall_2015/BME_464/Project/Apnea_Respiration_Control/ApneaRespirationControl-Software/main.c /Users/pdulapalli/Documents/Duke/Fall_2015/BME_464/Project/Apnea_Respiration_Control/ApneaRespirationControl-Software/ADXL313.c /Users/pdulapalli/Documents/Duke/Fall_2015/BME_464/Project/Apnea_Respiration_Control/ApneaRespirationControl-Software/ApneaMonitor.c /Users/pdulapalli/Documents/Duke/Fall_2015/BME_464/Project/Apnea_Respiration_Control/ApneaRespirationControl-Software/Globals.c /Users/pdulapalli/Documents/Duke/Fall_2015/BME_464/Project/Apnea_Respiration_Control/ApneaRespirationControl-Software/AuxLCD.c /Users/pdulapalli/Documents/Duke/Fall_2015/BME_464/Project/Apnea_Respiration_Control/ApneaRespirationControl-Software/PWMOut.c


CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/ApneaRespirationControl-Software.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=18F46K22
MP_PROCESSOR_OPTION_LD=18f46k22
MP_LINKER_DEBUG_OPTION=
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/591047608/Lcd.o: /Users/pdulapalli/Documents/Duke/Fall_2015/BME_464/Project/Apnea_Respiration_Control/ApneaRespirationControl-Software/Lcd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/591047608" 
	@${RM} ${OBJECTDIR}/_ext/591047608/Lcd.o.d 
	@${RM} ${OBJECTDIR}/_ext/591047608/Lcd.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION) -ms -oa-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/_ext/591047608/Lcd.o   /Users/pdulapalli/Documents/Duke/Fall_2015/BME_464/Project/Apnea_Respiration_Control/ApneaRespirationControl-Software/Lcd.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/591047608/Lcd.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/591047608/Lcd.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/591047608/DataManager.o: /Users/pdulapalli/Documents/Duke/Fall_2015/BME_464/Project/Apnea_Respiration_Control/ApneaRespirationControl-Software/DataManager.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/591047608" 
	@${RM} ${OBJECTDIR}/_ext/591047608/DataManager.o.d 
	@${RM} ${OBJECTDIR}/_ext/591047608/DataManager.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION) -ms -oa-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/_ext/591047608/DataManager.o   /Users/pdulapalli/Documents/Duke/Fall_2015/BME_464/Project/Apnea_Respiration_Control/ApneaRespirationControl-Software/DataManager.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/591047608/DataManager.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/591047608/DataManager.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/591047608/SPIComLink.o: /Users/pdulapalli/Documents/Duke/Fall_2015/BME_464/Project/Apnea_Respiration_Control/ApneaRespirationControl-Software/SPIComLink.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/591047608" 
	@${RM} ${OBJECTDIR}/_ext/591047608/SPIComLink.o.d 
	@${RM} ${OBJECTDIR}/_ext/591047608/SPIComLink.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION) -ms -oa-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/_ext/591047608/SPIComLink.o   /Users/pdulapalli/Documents/Duke/Fall_2015/BME_464/Project/Apnea_Respiration_Control/ApneaRespirationControl-Software/SPIComLink.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/591047608/SPIComLink.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/591047608/SPIComLink.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/591047608/main.o: /Users/pdulapalli/Documents/Duke/Fall_2015/BME_464/Project/Apnea_Respiration_Control/ApneaRespirationControl-Software/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/591047608" 
	@${RM} ${OBJECTDIR}/_ext/591047608/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/591047608/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION) -ms -oa-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/_ext/591047608/main.o   /Users/pdulapalli/Documents/Duke/Fall_2015/BME_464/Project/Apnea_Respiration_Control/ApneaRespirationControl-Software/main.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/591047608/main.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/591047608/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/591047608/ADXL313.o: /Users/pdulapalli/Documents/Duke/Fall_2015/BME_464/Project/Apnea_Respiration_Control/ApneaRespirationControl-Software/ADXL313.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/591047608" 
	@${RM} ${OBJECTDIR}/_ext/591047608/ADXL313.o.d 
	@${RM} ${OBJECTDIR}/_ext/591047608/ADXL313.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION) -ms -oa-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/_ext/591047608/ADXL313.o   /Users/pdulapalli/Documents/Duke/Fall_2015/BME_464/Project/Apnea_Respiration_Control/ApneaRespirationControl-Software/ADXL313.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/591047608/ADXL313.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/591047608/ADXL313.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/591047608/ApneaMonitor.o: /Users/pdulapalli/Documents/Duke/Fall_2015/BME_464/Project/Apnea_Respiration_Control/ApneaRespirationControl-Software/ApneaMonitor.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/591047608" 
	@${RM} ${OBJECTDIR}/_ext/591047608/ApneaMonitor.o.d 
	@${RM} ${OBJECTDIR}/_ext/591047608/ApneaMonitor.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION) -ms -oa-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/_ext/591047608/ApneaMonitor.o   /Users/pdulapalli/Documents/Duke/Fall_2015/BME_464/Project/Apnea_Respiration_Control/ApneaRespirationControl-Software/ApneaMonitor.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/591047608/ApneaMonitor.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/591047608/ApneaMonitor.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/591047608/Globals.o: /Users/pdulapalli/Documents/Duke/Fall_2015/BME_464/Project/Apnea_Respiration_Control/ApneaRespirationControl-Software/Globals.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/591047608" 
	@${RM} ${OBJECTDIR}/_ext/591047608/Globals.o.d 
	@${RM} ${OBJECTDIR}/_ext/591047608/Globals.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION) -ms -oa-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/_ext/591047608/Globals.o   /Users/pdulapalli/Documents/Duke/Fall_2015/BME_464/Project/Apnea_Respiration_Control/ApneaRespirationControl-Software/Globals.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/591047608/Globals.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/591047608/Globals.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/591047608/AuxLCD.o: /Users/pdulapalli/Documents/Duke/Fall_2015/BME_464/Project/Apnea_Respiration_Control/ApneaRespirationControl-Software/AuxLCD.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/591047608" 
	@${RM} ${OBJECTDIR}/_ext/591047608/AuxLCD.o.d 
	@${RM} ${OBJECTDIR}/_ext/591047608/AuxLCD.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION) -ms -oa-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/_ext/591047608/AuxLCD.o   /Users/pdulapalli/Documents/Duke/Fall_2015/BME_464/Project/Apnea_Respiration_Control/ApneaRespirationControl-Software/AuxLCD.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/591047608/AuxLCD.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/591047608/AuxLCD.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/591047608/PWMOut.o: /Users/pdulapalli/Documents/Duke/Fall_2015/BME_464/Project/Apnea_Respiration_Control/ApneaRespirationControl-Software/PWMOut.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/591047608" 
	@${RM} ${OBJECTDIR}/_ext/591047608/PWMOut.o.d 
	@${RM} ${OBJECTDIR}/_ext/591047608/PWMOut.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION) -ms -oa-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/_ext/591047608/PWMOut.o   /Users/pdulapalli/Documents/Duke/Fall_2015/BME_464/Project/Apnea_Respiration_Control/ApneaRespirationControl-Software/PWMOut.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/591047608/PWMOut.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/591047608/PWMOut.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
else
${OBJECTDIR}/_ext/591047608/Lcd.o: /Users/pdulapalli/Documents/Duke/Fall_2015/BME_464/Project/Apnea_Respiration_Control/ApneaRespirationControl-Software/Lcd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/591047608" 
	@${RM} ${OBJECTDIR}/_ext/591047608/Lcd.o.d 
	@${RM} ${OBJECTDIR}/_ext/591047608/Lcd.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -ms -oa-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/_ext/591047608/Lcd.o   /Users/pdulapalli/Documents/Duke/Fall_2015/BME_464/Project/Apnea_Respiration_Control/ApneaRespirationControl-Software/Lcd.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/591047608/Lcd.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/591047608/Lcd.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/591047608/DataManager.o: /Users/pdulapalli/Documents/Duke/Fall_2015/BME_464/Project/Apnea_Respiration_Control/ApneaRespirationControl-Software/DataManager.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/591047608" 
	@${RM} ${OBJECTDIR}/_ext/591047608/DataManager.o.d 
	@${RM} ${OBJECTDIR}/_ext/591047608/DataManager.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -ms -oa-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/_ext/591047608/DataManager.o   /Users/pdulapalli/Documents/Duke/Fall_2015/BME_464/Project/Apnea_Respiration_Control/ApneaRespirationControl-Software/DataManager.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/591047608/DataManager.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/591047608/DataManager.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/591047608/SPIComLink.o: /Users/pdulapalli/Documents/Duke/Fall_2015/BME_464/Project/Apnea_Respiration_Control/ApneaRespirationControl-Software/SPIComLink.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/591047608" 
	@${RM} ${OBJECTDIR}/_ext/591047608/SPIComLink.o.d 
	@${RM} ${OBJECTDIR}/_ext/591047608/SPIComLink.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -ms -oa-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/_ext/591047608/SPIComLink.o   /Users/pdulapalli/Documents/Duke/Fall_2015/BME_464/Project/Apnea_Respiration_Control/ApneaRespirationControl-Software/SPIComLink.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/591047608/SPIComLink.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/591047608/SPIComLink.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/591047608/main.o: /Users/pdulapalli/Documents/Duke/Fall_2015/BME_464/Project/Apnea_Respiration_Control/ApneaRespirationControl-Software/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/591047608" 
	@${RM} ${OBJECTDIR}/_ext/591047608/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/591047608/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -ms -oa-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/_ext/591047608/main.o   /Users/pdulapalli/Documents/Duke/Fall_2015/BME_464/Project/Apnea_Respiration_Control/ApneaRespirationControl-Software/main.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/591047608/main.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/591047608/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/591047608/ADXL313.o: /Users/pdulapalli/Documents/Duke/Fall_2015/BME_464/Project/Apnea_Respiration_Control/ApneaRespirationControl-Software/ADXL313.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/591047608" 
	@${RM} ${OBJECTDIR}/_ext/591047608/ADXL313.o.d 
	@${RM} ${OBJECTDIR}/_ext/591047608/ADXL313.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -ms -oa-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/_ext/591047608/ADXL313.o   /Users/pdulapalli/Documents/Duke/Fall_2015/BME_464/Project/Apnea_Respiration_Control/ApneaRespirationControl-Software/ADXL313.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/591047608/ADXL313.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/591047608/ADXL313.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/591047608/ApneaMonitor.o: /Users/pdulapalli/Documents/Duke/Fall_2015/BME_464/Project/Apnea_Respiration_Control/ApneaRespirationControl-Software/ApneaMonitor.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/591047608" 
	@${RM} ${OBJECTDIR}/_ext/591047608/ApneaMonitor.o.d 
	@${RM} ${OBJECTDIR}/_ext/591047608/ApneaMonitor.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -ms -oa-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/_ext/591047608/ApneaMonitor.o   /Users/pdulapalli/Documents/Duke/Fall_2015/BME_464/Project/Apnea_Respiration_Control/ApneaRespirationControl-Software/ApneaMonitor.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/591047608/ApneaMonitor.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/591047608/ApneaMonitor.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/591047608/Globals.o: /Users/pdulapalli/Documents/Duke/Fall_2015/BME_464/Project/Apnea_Respiration_Control/ApneaRespirationControl-Software/Globals.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/591047608" 
	@${RM} ${OBJECTDIR}/_ext/591047608/Globals.o.d 
	@${RM} ${OBJECTDIR}/_ext/591047608/Globals.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -ms -oa-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/_ext/591047608/Globals.o   /Users/pdulapalli/Documents/Duke/Fall_2015/BME_464/Project/Apnea_Respiration_Control/ApneaRespirationControl-Software/Globals.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/591047608/Globals.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/591047608/Globals.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/591047608/AuxLCD.o: /Users/pdulapalli/Documents/Duke/Fall_2015/BME_464/Project/Apnea_Respiration_Control/ApneaRespirationControl-Software/AuxLCD.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/591047608" 
	@${RM} ${OBJECTDIR}/_ext/591047608/AuxLCD.o.d 
	@${RM} ${OBJECTDIR}/_ext/591047608/AuxLCD.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -ms -oa-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/_ext/591047608/AuxLCD.o   /Users/pdulapalli/Documents/Duke/Fall_2015/BME_464/Project/Apnea_Respiration_Control/ApneaRespirationControl-Software/AuxLCD.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/591047608/AuxLCD.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/591047608/AuxLCD.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/591047608/PWMOut.o: /Users/pdulapalli/Documents/Duke/Fall_2015/BME_464/Project/Apnea_Respiration_Control/ApneaRespirationControl-Software/PWMOut.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/591047608" 
	@${RM} ${OBJECTDIR}/_ext/591047608/PWMOut.o.d 
	@${RM} ${OBJECTDIR}/_ext/591047608/PWMOut.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -ms -oa-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/_ext/591047608/PWMOut.o   /Users/pdulapalli/Documents/Duke/Fall_2015/BME_464/Project/Apnea_Respiration_Control/ApneaRespirationControl-Software/PWMOut.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/591047608/PWMOut.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/591047608/PWMOut.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/ApneaRespirationControl-Software.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_LD} $(MP_EXTRA_LD_PRE)   -p$(MP_PROCESSOR_OPTION_LD)  -w -x -u_DEBUG -m"${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map"  -z__MPLAB_BUILD=1  -u_CRUNTIME -z__MPLAB_DEBUG=1 -z__MPLAB_DEBUGGER_PK3=1 $(MP_LINKER_DEBUG_OPTION) -l ${MP_CC_DIR}/../lib  -o dist/${CND_CONF}/${IMAGE_TYPE}/ApneaRespirationControl-Software.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}   
else
dist/${CND_CONF}/${IMAGE_TYPE}/ApneaRespirationControl-Software.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_LD} $(MP_EXTRA_LD_PRE)   -p$(MP_PROCESSOR_OPTION_LD)  -w  -m"${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map"  -z__MPLAB_BUILD=1  -u_CRUNTIME -l ${MP_CC_DIR}/../lib  -o dist/${CND_CONF}/${IMAGE_TYPE}/ApneaRespirationControl-Software.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}   
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell "${PATH_TO_IDE_BIN}"mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
