#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux-x86
CND_DLIB_EXT=so
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/src/bbudf.o \
	${OBJECTDIR}/src/curl.o \
	${OBJECTDIR}/src/file.o \
	${OBJECTDIR}/src/inet.o \
	${OBJECTDIR}/src/logger.o \
	${OBJECTDIR}/src/stdafx.o \
	${OBJECTDIR}/src/string.o \
	${OBJECTDIR}/src/xmlreader.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-lxml2 -lib_util -lcurl

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libbbudf.${CND_DLIB_EXT}

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libbbudf.${CND_DLIB_EXT}: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libbbudf.${CND_DLIB_EXT} ${OBJECTFILES} ${LDLIBSOPTIONS} -shared -fPIC

${OBJECTDIR}/src/bbudf.o: src/bbudf.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I/usr/include/libxml2 -I/usr/include/firebird -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/bbudf.o src/bbudf.cpp

${OBJECTDIR}/src/curl.o: src/curl.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I/usr/include/libxml2 -I/usr/include/firebird -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/curl.o src/curl.cpp

${OBJECTDIR}/src/file.o: src/file.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I/usr/include/libxml2 -I/usr/include/firebird -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/file.o src/file.cpp

${OBJECTDIR}/src/inet.o: src/inet.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I/usr/include/libxml2 -I/usr/include/firebird -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/inet.o src/inet.cpp

${OBJECTDIR}/src/logger.o: src/logger.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I/usr/include/libxml2 -I/usr/include/firebird -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/logger.o src/logger.cpp

${OBJECTDIR}/src/stdafx.o: src/stdafx.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I/usr/include/libxml2 -I/usr/include/firebird -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/stdafx.o src/stdafx.cpp

${OBJECTDIR}/src/string.o: src/string.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I/usr/include/libxml2 -I/usr/include/firebird -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/string.o src/string.cpp

${OBJECTDIR}/src/xmlreader.o: src/xmlreader.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I/usr/include/libxml2 -I/usr/include/firebird -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/xmlreader.o src/xmlreader.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libbbudf.${CND_DLIB_EXT}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
