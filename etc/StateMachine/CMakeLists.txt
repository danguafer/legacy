CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT("Silexars State Machine")

INCLUDE("../../Silexars.cmake")

AUX_SOURCE_DIRECTORY(. SOURCES)

ADD_SILEXARS_LIBRARY(SilexarsUtilsStateMachine ${SOURCES})
