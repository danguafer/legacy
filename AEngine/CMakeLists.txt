CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

PROJECT("Silexars AEngine")

INCLUDE("../Silexars.cmake")

AUX_SOURCE_DIRECTORY(. SOURCES)
AUX_SOURCE_DIRECTORY(Renderers/ SOURCES)
AUX_SOURCE_DIRECTORY(Cinema/ SOURCES)
AUX_SOURCE_DIRECTORY(Controllers/ SOURCES)
AUX_SOURCE_DIRECTORY(Managers/ SOURCES)

ADD_SILEXARS_LIBRARY(SilexarsAEngine ${SOURCES})
