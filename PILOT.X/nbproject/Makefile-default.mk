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
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/PILOT.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/PILOT.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED="../Common Files Robot Dev Board/analog.c" "../Common Files Robot Dev Board/delay.c" "../Common Files Robot Dev Board/lcd.c" "pilot hardware setup.c" pilot.c odometrie.c deplacements.c asservissements.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/362702250/analog.o ${OBJECTDIR}/_ext/362702250/delay.o ${OBJECTDIR}/_ext/362702250/lcd.o "${OBJECTDIR}/pilot hardware setup.o" ${OBJECTDIR}/pilot.o ${OBJECTDIR}/odometrie.o ${OBJECTDIR}/deplacements.o ${OBJECTDIR}/asservissements.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/362702250/analog.o.d ${OBJECTDIR}/_ext/362702250/delay.o.d ${OBJECTDIR}/_ext/362702250/lcd.o.d "${OBJECTDIR}/pilot hardware setup.o.d" ${OBJECTDIR}/pilot.o.d ${OBJECTDIR}/odometrie.o.d ${OBJECTDIR}/deplacements.o.d ${OBJECTDIR}/asservissements.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/362702250/analog.o ${OBJECTDIR}/_ext/362702250/delay.o ${OBJECTDIR}/_ext/362702250/lcd.o ${OBJECTDIR}/pilot\ hardware\ setup.o ${OBJECTDIR}/pilot.o ${OBJECTDIR}/odometrie.o ${OBJECTDIR}/deplacements.o ${OBJECTDIR}/asservissements.o

# Source Files
SOURCEFILES=../Common Files Robot Dev Board/analog.c ../Common Files Robot Dev Board/delay.c ../Common Files Robot Dev Board/lcd.c pilot hardware setup.c pilot.c odometrie.c deplacements.c asservissements.c


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
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/PILOT.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=33FJ128MC804
MP_LINKER_FILE_OPTION=,--script=p33FJ128MC804.gld
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/362702250/analog.o: ../Common\ Files\ Robot\ Dev\ Board/analog.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/362702250 
	@${RM} ${OBJECTDIR}/_ext/362702250/analog.o.d 
	@${RM} ${OBJECTDIR}/_ext/362702250/analog.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  "../Common Files Robot Dev Board/analog.c"  -o ${OBJECTDIR}/_ext/362702250/analog.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/362702250/analog.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/362702250/analog.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/362702250/delay.o: ../Common\ Files\ Robot\ Dev\ Board/delay.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/362702250 
	@${RM} ${OBJECTDIR}/_ext/362702250/delay.o.d 
	@${RM} ${OBJECTDIR}/_ext/362702250/delay.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  "../Common Files Robot Dev Board/delay.c"  -o ${OBJECTDIR}/_ext/362702250/delay.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/362702250/delay.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/362702250/delay.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/362702250/lcd.o: ../Common\ Files\ Robot\ Dev\ Board/lcd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/362702250 
	@${RM} ${OBJECTDIR}/_ext/362702250/lcd.o.d 
	@${RM} ${OBJECTDIR}/_ext/362702250/lcd.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  "../Common Files Robot Dev Board/lcd.c"  -o ${OBJECTDIR}/_ext/362702250/lcd.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/362702250/lcd.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/362702250/lcd.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/pilot\ hardware\ setup.o: pilot\ hardware\ setup.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/pilot\ hardware\ setup.o.d 
	@${RM} "${OBJECTDIR}/pilot hardware setup.o" 
	${MP_CC} $(MP_EXTRA_CC_PRE)  "pilot hardware setup.c"  -o "${OBJECTDIR}/pilot hardware setup.o"  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/pilot hardware setup.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/pilot hardware setup.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/pilot.o: pilot.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/pilot.o.d 
	@${RM} ${OBJECTDIR}/pilot.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pilot.c  -o ${OBJECTDIR}/pilot.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/pilot.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/pilot.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/odometrie.o: odometrie.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/odometrie.o.d 
	@${RM} ${OBJECTDIR}/odometrie.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  odometrie.c  -o ${OBJECTDIR}/odometrie.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/odometrie.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/odometrie.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/deplacements.o: deplacements.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/deplacements.o.d 
	@${RM} ${OBJECTDIR}/deplacements.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  deplacements.c  -o ${OBJECTDIR}/deplacements.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/deplacements.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/deplacements.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/asservissements.o: asservissements.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/asservissements.o.d 
	@${RM} ${OBJECTDIR}/asservissements.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  asservissements.c  -o ${OBJECTDIR}/asservissements.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/asservissements.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/asservissements.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
else
${OBJECTDIR}/_ext/362702250/analog.o: ../Common\ Files\ Robot\ Dev\ Board/analog.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/362702250 
	@${RM} ${OBJECTDIR}/_ext/362702250/analog.o.d 
	@${RM} ${OBJECTDIR}/_ext/362702250/analog.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  "../Common Files Robot Dev Board/analog.c"  -o ${OBJECTDIR}/_ext/362702250/analog.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/362702250/analog.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/362702250/analog.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/362702250/delay.o: ../Common\ Files\ Robot\ Dev\ Board/delay.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/362702250 
	@${RM} ${OBJECTDIR}/_ext/362702250/delay.o.d 
	@${RM} ${OBJECTDIR}/_ext/362702250/delay.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  "../Common Files Robot Dev Board/delay.c"  -o ${OBJECTDIR}/_ext/362702250/delay.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/362702250/delay.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/362702250/delay.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/362702250/lcd.o: ../Common\ Files\ Robot\ Dev\ Board/lcd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/362702250 
	@${RM} ${OBJECTDIR}/_ext/362702250/lcd.o.d 
	@${RM} ${OBJECTDIR}/_ext/362702250/lcd.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  "../Common Files Robot Dev Board/lcd.c"  -o ${OBJECTDIR}/_ext/362702250/lcd.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/362702250/lcd.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/362702250/lcd.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/pilot\ hardware\ setup.o: pilot\ hardware\ setup.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/pilot\ hardware\ setup.o.d 
	@${RM} "${OBJECTDIR}/pilot hardware setup.o" 
	${MP_CC} $(MP_EXTRA_CC_PRE)  "pilot hardware setup.c"  -o "${OBJECTDIR}/pilot hardware setup.o"  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/pilot hardware setup.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/pilot hardware setup.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/pilot.o: pilot.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/pilot.o.d 
	@${RM} ${OBJECTDIR}/pilot.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pilot.c  -o ${OBJECTDIR}/pilot.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/pilot.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/pilot.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/odometrie.o: odometrie.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/odometrie.o.d 
	@${RM} ${OBJECTDIR}/odometrie.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  odometrie.c  -o ${OBJECTDIR}/odometrie.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/odometrie.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/odometrie.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/deplacements.o: deplacements.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/deplacements.o.d 
	@${RM} ${OBJECTDIR}/deplacements.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  deplacements.c  -o ${OBJECTDIR}/deplacements.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/deplacements.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/deplacements.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/asservissements.o: asservissements.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/asservissements.o.d 
	@${RM} ${OBJECTDIR}/asservissements.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  asservissements.c  -o ${OBJECTDIR}/asservissements.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/asservissements.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/asservissements.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemblePreproc
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/PILOT.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/PILOT.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf  -mreserve=data@0x800:0x81F -mreserve=data@0x820:0x821 -mreserve=data@0x822:0x823 -mreserve=data@0x824:0x825 -mreserve=data@0x826:0x84F   -Wl,,--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem$(MP_EXTRA_LD_POST) 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/PILOT.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/PILOT.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -omf=elf -Wl,,--defsym=__MPLAB_BUILD=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem$(MP_EXTRA_LD_POST) 
	${MP_CC_DIR}/xc16-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/PILOT.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -a  -omf=elf  
	
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
