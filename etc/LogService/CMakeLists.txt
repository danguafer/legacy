CMAKE_MINIMUM_REQUIRED(VERSION 2.6)



PROJECT("VeritasetcLogService")



INCLUDE("../../Silexars.cmake")



AUX_SOURCE_DIRECTORY(. SOURCES)


ADD_SILEXARS_LIBRARY(${PROJECT_NAME} ${SOURCES})
