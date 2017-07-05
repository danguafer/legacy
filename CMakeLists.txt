CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

PROJECT("Veritas")

ADD_SUBDIRECTORY(Math Silexars/Math)

ADD_SUBDIRECTORY(Data Silexars/Data)

ADD_SUBDIRECTORY(System Silexars/System)

ADD_SUBDIRECTORY(etc/StateMachine Silexars/etc/StateMachine)
ADD_SUBDIRECTORY(etc/Socket Silexars/etc/Socket)
ADD_SUBDIRECTORY(etc/LogService Silexars/etc/LogService)
ADD_SUBDIRECTORY(etc/Parser Silexars/etc/Parser)

ADD_SUBDIRECTORY(Graphics/API Silexars/Graphics/API)
ADD_SUBDIRECTORY(Graphics/Image Silexars/Graphics/Image)
ADD_SUBDIRECTORY(Graphics/Canvas Silexars/Graphics/Canvas)
ADD_SUBDIRECTORY(Graphics/Font Silexars/Graphics/Font)

ADD_SUBDIRECTORY(AEngine Silexars/AEngine)
