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
CND_PLATFORM=GNU-Linux
CND_DLIB_EXT=so
CND_CONF=KaliRelease
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/Buzzer.o \
	${OBJECTDIR}/Camera.o \
	${OBJECTDIR}/InfraredSensor.o \
	${OBJECTDIR}/KaliRobot.o \
	${OBJECTDIR}/LeftWheels.o \
	${OBJECTDIR}/Logging.o \
	${OBJECTDIR}/Remote.o \
	${OBJECTDIR}/RightWheels.o \
	${OBJECTDIR}/Sensors.o \
	${OBJECTDIR}/Servo.o \
	${OBJECTDIR}/Speaker.o \
	${OBJECTDIR}/UltrasonicSensor.o \
	${OBJECTDIR}/Validation.o \
	${OBJECTDIR}/Wheel.o \
	${OBJECTDIR}/Wheels.o \
	${OBJECTDIR}/kali.o


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
LDLIBSOPTIONS=/usr/lib/libwiringPi.so /usr/local/lib//libopencv_core.so /usr/local/lib/libopencv_highgui.so /usr/local/lib/libopencv_imgproc.so /usr/local/lib/libopencv_objdetect.so /usr/local/lib/libopencv_video.so /usr/local/lib/libopencv_videoio.so /usr/local/lib/libopencv_imgcodecs.so /usr/local/lib/libopencv_face.so /usr/lib/arm-linux-gnueabihf/libsqlite3.so /usr/lib/arm-linux-gnueabihf/libespeak-ng.so /usr/lib/arm-linux-gnueabihf/libncurses.so

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/kali

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/kali: /usr/lib/libwiringPi.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/kali: /usr/local/lib//libopencv_core.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/kali: /usr/local/lib/libopencv_highgui.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/kali: /usr/local/lib/libopencv_imgproc.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/kali: /usr/local/lib/libopencv_objdetect.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/kali: /usr/local/lib/libopencv_video.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/kali: /usr/local/lib/libopencv_videoio.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/kali: /usr/local/lib/libopencv_imgcodecs.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/kali: /usr/local/lib/libopencv_face.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/kali: /usr/lib/arm-linux-gnueabihf/libsqlite3.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/kali: /usr/lib/arm-linux-gnueabihf/libespeak-ng.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/kali: /usr/lib/arm-linux-gnueabihf/libncurses.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/kali: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/kali ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/Buzzer.o: Buzzer.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I/usr/local/include/opencv4 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Buzzer.o Buzzer.cpp

${OBJECTDIR}/Camera.o: Camera.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I/usr/local/include/opencv4 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Camera.o Camera.cpp

${OBJECTDIR}/InfraredSensor.o: InfraredSensor.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I/usr/local/include/opencv4 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/InfraredSensor.o InfraredSensor.cpp

${OBJECTDIR}/KaliRobot.o: KaliRobot.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I/usr/local/include/opencv4 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/KaliRobot.o KaliRobot.cpp

${OBJECTDIR}/LeftWheels.o: LeftWheels.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I/usr/local/include/opencv4 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/LeftWheels.o LeftWheels.cpp

${OBJECTDIR}/Logging.o: Logging.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I/usr/local/include/opencv4 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Logging.o Logging.cpp

${OBJECTDIR}/Remote.o: Remote.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I/usr/local/include/opencv4 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Remote.o Remote.cpp

${OBJECTDIR}/RightWheels.o: RightWheels.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I/usr/local/include/opencv4 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/RightWheels.o RightWheels.cpp

${OBJECTDIR}/Sensors.o: Sensors.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I/usr/local/include/opencv4 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Sensors.o Sensors.cpp

${OBJECTDIR}/Servo.o: Servo.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I/usr/local/include/opencv4 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Servo.o Servo.cpp

${OBJECTDIR}/Speaker.o: Speaker.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I/usr/local/include/opencv4 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Speaker.o Speaker.cpp

${OBJECTDIR}/UltrasonicSensor.o: UltrasonicSensor.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I/usr/local/include/opencv4 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/UltrasonicSensor.o UltrasonicSensor.cpp

${OBJECTDIR}/Validation.o: Validation.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I/usr/local/include/opencv4 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Validation.o Validation.cpp

${OBJECTDIR}/Wheel.o: Wheel.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I/usr/local/include/opencv4 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Wheel.o Wheel.cpp

${OBJECTDIR}/Wheels.o: Wheels.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I/usr/local/include/opencv4 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Wheels.o Wheels.cpp

${OBJECTDIR}/kali.o: kali.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I/usr/local/include/opencv4 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/kali.o kali.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} -r ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libwiringPi.so ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libopencv_core.so ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libopencv_highgui.so ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libopencv_imgproc.so ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libopencv_objdetect.so ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libopencv_video.so ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libopencv_videoio.so ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libopencv_imgcodecs.so ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libopencv_face.so ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libsqlite3.so ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libespeak-ng.so ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libncurses.so
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/kali

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
