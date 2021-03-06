GET_FILENAME_COMPONENT(SILEXARS_PATH "${CMAKE_CURRENT_LIST_FILE}" PATH)

INCLUDE("${SILEXARS_PATH}/DetectARCH.cmake")
INCLUDE("${SILEXARS_PATH}/DetectOS.cmake")

INCLUDE_DIRECTORIES("${SILEXARS_PATH}/..")
LINK_DIRECTORIES("${SILEXARS_PATH}/lib/${SILEXARS_TARGET_SYSTEM}/${SILEXARS_TARGET_ARCH}")

#INCLUDE_DIRECTORIES("/usr/lib/x86_64-linux-gnu/glib-2.0/include" "/usr/include/glib-2.0")
INCLUDE_DIRECTORIES("${SILEXARS_PATH}/System/third-party/include/")

FUNCTION(TARGET_LINK_SILEXARS_SYSTEM TARGET)
    IF(NOT SILEXARS_SYSTEM_LINKED)
        SET(SILEXARS_SYSTEM_LINKED "LINKED" PARENT_SCOPE)
        LINK_DIRECTORIES("${SILEXARS_PATH}/System/third-party/lib/${SILEXARS_TARGET_SYSTEM}/${SILEXARS_TARGET_ARCH}/")

        IF(ANDROID)
            SET(SYSTEMLIB -Wl,--whole-archive -lSilexarsSystem -Wl,--no-whole-archive)
        ELSE()
            SET(SYSTEMLIB SilexarsSystem)
        ENDIF()
#        TARGET_LINK_LIBRARIES(${TARGET} ${SYSTEMLIB})
        TARGET_LINK_LIBRARIES(${TARGET} "${SILEXARS_PATH}/lib/${SILEXARS_TARGET_SYSTEM}/${SILEXARS_TARGET_ARCH}/libSilexarsSystem.a")

        IF(WINDOWS)
            SET(CMAKE_EXE_LINKER_FLAGS "-static -static-libgcc -static-libstdc++")
            TARGET_LINK_LIBRARIES(${TARGET} "${SILEXARS_PATH}/System/third-party/lib/${SILEXARS_TARGET_SYSTEM}/${SILEXARS_TARGET_ARCH}/glew32s.lib" opengl32 gdi32 WS2_32 Iphlpapi)
        ELSEIF(LINUX)
            TARGET_LINK_LIBRARIES(${TARGET} X11 openal rt GL GLEW pthread bluetooth)
        ELSEIF(ANDROID)
            TARGET_LINK_LIBRARIES(${TARGET} log android EGL GLESv2) # GLESv3
        ELSEIF(OSX)
            TARGET_LINK_LIBRARIES(${TARGET} "-framework Cocoa" "-framework OpenGL" "-framework GLUT" GLEW)
        ENDIF()

        TARGET_LINK_SILEXARS_DATA(${TARGET})
    ENDIF()
ENDFUNCTION(TARGET_LINK_SILEXARS_SYSTEM)

FUNCTION(TARGET_LINK_SILEXARS_GRAPHICS_API TARGET)
    IF(NOT SILEXARS_GRAPHICS_API_LINKED)
        SET(SILEXARS_GRAPHICS_API_LINKED "LINKED" PARENT_SCOPE)
        TARGET_LINK_LIBRARIES(${TARGET} SilexarsGraphicsAPI)
    ENDIF()
ENDFUNCTION()

FUNCTION(TARGET_LINK_SILEXARS_GRAPHICS_CANVAS TARGET)
    IF(NOT SILEXARS_GRAPHICS_API_LINKED)
        SET(SILEXARS_GRAPHICS_API_LINKED "LINKED" PARENT_SCOPE)
        TARGET_LINK_LIBRARIES(${TARGET} SilexarsGraphicsCanvas)
        TARGET_LINK_SILEXARS_GRAPHICS_API(${TARGET})
        TARGET_LINK_SILEXARS_GRAPHICS_FONT(${TARGET})
        TARGET_LINK_SILEXARS_MATH(${TARGET})
    ENDIF()
ENDFUNCTION()

FUNCTION(TARGET_LINK_SILEXARS_MATH TARGET)
    IF(NOT SILEXARS_MATH_LINKED)
        SET(SILEXARS_MATH_LIKED "LINKED" PARENT_SCOPE)
        TARGET_LINK_LIBRARIES(${TARGET} SilexarsMath)
    ENDIF()
ENDFUNCTION()

FUNCTION(TARGET_LINK_SILEXARS_AENGINE TARGET)
    IF(NOT SILEXARS_AENGINE_LINKED)
        SET(SILEXARS_AENGINE_LINKED "LINKED" PARENT_SCOPE)
        TARGET_LINK_LIBRARIES(${TARGET} SilexarsAEngine)
        TARGET_LINK_SILEXARS_GRAPHICS_CANVAS(${TARGET})
        TARGET_LINK_SILEXARS_GRAPHICS_API(${TARGET})
        TARGET_LINK_SILEXARS_GRAPHICS_IMAGE(${TARGET})
        TARGET_LINK_SILEXARS_SYSTEM(${TARGET})
        TARGET_LINK_SILEXARS_UTILS_STATEMACHINE(${TARGET})
        TARGET_LINK_SILEXARS_MATH(${TARGET})
    ENDIF()
ENDFUNCTION()

FUNCTION(TARGET_LINK_SILEXARS_GRAPHICS_IMAGE TARGET)
    IF(NOT SILEXARS_GRAPHICS_IMAGE_LINKED)
        SET(SILEXARS_GRAPHICS_IMAGE_LINKED "LINKED" PARENT_SCOPE)
        TARGET_LINK_LIBRARIES(${TARGET} SilexarsGraphicsImage)
        TARGET_LINK_SILEXARS_SYSTEM(${TARGET})
    ENDIF()
ENDFUNCTION()

FUNCTION(TARGET_LINK_SILEXARS_GRAPHICS_FONT TARGET)
    IF(NOT SILEXARS_GRAPHICS_FONT_LINKED)
        SET(SILEXARS_GRAPHICS_FONT_LINKED "LINKED" PARENT_SCOPE)
        TARGET_LINK_LIBRARIES(${TARGET} SilexarsGraphicsFont)
        TARGET_LINK_LIBRARIES(${TARGET} freetype)
    ENDIF()
ENDFUNCTION()

FUNCTION(TARGET_LINK_SILEXARS_GRAPHICS_UI TARGET)
    IF(NOT SILEXARS_GRAPHICS_UI_LINKED)
        SET(SILEXARS_GRAPHICS_UI_LINKED "LINKED" PARENT_SCOPE)
        TARGET_LINK_LIBRARIES(${TARGET} SilexarsGraphicsUI)
        TARGET_LINK_SILEXARS_GRAPHICS_CANVAS(${TARGET})
    ENDIF()
ENDFUNCTION()

FUNCTION(TARGET_LINK_SILEXARS_UTILS_STATEMACHINE TARGET)
    IF(NOT SILEXARS_UTILS_STATEMACHINE_LINKED)
        SET(SILEXARS_UTILS_STATEMACHINE_LINKED "LINKED" PARENT_SCOPE)
        TARGET_LINK_LIBRARIES(${TARGET} SilexarsUtilsStateMachine)
    ENDIF()
ENDFUNCTION()

FUNCTION(TARGET_LINK_SILEXARS_DATA TARGET)
    IF(NOT SILEXARS_DATA_LINKED)
        SET(SILEXARS_DATA_LINKED "LINKED" PARENT_SCOPE)
        TARGET_LINK_LIBRARIES(${TARGET} SilexarsData)
    ENDIF()
ENDFUNCTION()

FUNCTION(TARGET_LINK_SILEXARS_LANGUAGE_PARSER TARGET)
    IF(NOT SILEXARS_LANGUAGE_PARSER_LINKED)
        SET(SILEXARS_LANGUAGE_PARSER_LINKED "LINKED" PARENT_SCOPE)
        TARGET_LINK_LIBRARIES(${TARGET} SilexarsLanguageParser)
    ENDIF()
ENDFUNCTION()

#SET(CMAKE_CXX_FLAGS ${CMAKE_CSS_FLAGS} "-fPIC")

FUNCTION(ADD_SILEXARS_LIBRARY TARGET)
    LIST(REMOVE_AT ARGV 0)
    IF(NOT IOS OR OSX)
        FOREACH(FILE ${ARGV})
            IF (${FILE} MATCHES "[.]mm")
                LIST(REMOVE_ITEM ARGV ${FILE})
            ENDIF()
        ENDFOREACH()
    ENDIF()
    ADD_LIBRARY(${TARGET} ${ARGV})
    ADD_CUSTOM_COMMAND(TARGET ${TARGET} COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${TARGET}> "${SILEXARS_PATH}/lib/${SILEXARS_TARGET_SYSTEM}/${SILEXARS_TARGET_ARCH}/lib${TARGET}.a")
ENDFUNCTION(ADD_SILEXARS_LIBRARY)

FUNCTION(VERITAS_ADD_EXECUTABLE TARGET)
    LIST(REMOVE_AT ARGV 0)
    IF(NOT IOS OR OSX)
        FOREACH(FILE ${ARGV})
            IF (${FILE} MATCHES "[.]mm")
                LIST(REMOVE_ITEM ARGV ${FILE})
            ENDIF()
        ENDFOREACH()
    ENDIF()

    IF(ANDROID)
        # Write sdk.dir="${ANDROID_SDK}" to third-party/android/framework/local.properties

        IF(CMAKE_BUILD_TYPE MATCHES DEBUG)
            SET(ANDROID_BUILD_CMD "assembleDebug")
            SET(ANDROID_BUILD_TYPE "debug")
        ELSE()
            SET(ANDROID_BUILD_CMD "assembleRelease")
            SET(ANDROID_BUILD_TYPE "release")
        ENDIF()

        ADD_LIBRARY(${TARGET} MODULE ${ARGV})
        ADD_CUSTOM_COMMAND(TARGET ${TARGET} COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${TARGET}> "${SILEXARS_PATH}/third-party/android/framework/app/src/main/jniLibs/${ANDROID_ABI}/libnative-activity.so")
        ADD_CUSTOM_COMMAND(TARGET ${TARGET} COMMAND echo Building apk)
        ADD_CUSTOM_COMMAND(TARGET ${TARGET} COMMAND ${SILEXARS_PATH}/third-party/android/LiveWallpaper/gradlew -p ${SILEXARS_PATH}/third-party/android/framework/ ${ANDROID_BUILD_CMD})
        ADD_CUSTOM_COMMAND(TARGET ${TARGET} COMMAND echo Sending apk to device and installing it)
        # Change app-${ANDROID_ABI} to app-${SILEXARS_TARGET_ARCH}. But the detection needs to be fixed first because it's using the host arch.
#2        ADD_CUSTOM_COMMAND(TARGET ${TARGET} COMMAND ${ANDROID_SDK}/platform-tools/adb -s 614f0744 install -r ${SILEXARS_PATH}/third-party/android/framework/app/build/outputs/apk/app-arm-debug.apk)

        ADD_CUSTOM_COMMAND(TARGET ${TARGET} COMMAND ${ANDROID_SDK}/platform-tools/adb install -r ${SILEXARS_PATH}/third-party/android/framework/app/build/outputs/apk/app-${ANDROID_BUILD_TYPE}.apk)
#        ADD_CUSTOM_COMMAND(TARGET ${TARGET} COMMAND echo Starting application)
        ADD_CUSTOM_COMMAND(TARGET ${TARGET} COMMAND ${ANDROID_SDK}/platform-tools/adb shell am start -n com.silexars.framework/android.app.NativeActivity)
    ELSE()
        ADD_EXECUTABLE(${TARGET} ${ARGV})
    ENDIF()

    IF(DESKTOP)
        ADD_CUSTOM_COMMAND(TARGET ${TARGET} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:${TARGET}>)
    ENDIF()
ENDFUNCTION()

FUNCTION(ADD_SILEXARS_LIVEWALLPAPER TARGET)
    LIST(REMOVE_AT ARGV 0)
    IF(ANDROID)
        FOREACH(FILE ${ARGV})
            IF (${FILE} MATCHES "[.]mm")
                LIST(REMOVE_ITEM ARGV ${FILE})
            ENDIF()
        ENDFOREACH()

        IF(CMAKE_BUILD_TYPE MATCHES DEBUG)
            SET(ANDROID_BUILD_CMD "assembleDebug")
            SET(ANDROID_BUILD_TYPE "debug")
        ELSE()
            SET(ANDROID_BUILD_CMD "assembleRelease")
            SET(ANDROID_BUILD_TYPE "release")
        ENDIF()

        ADD_LIBRARY(${TARGET} MODULE ${ARGV})
        ADD_CUSTOM_COMMAND(TARGET ${TARGET} COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${TARGET}> "${SILEXARS_PATH}/third-party/android/LiveWallpaper/app/src/main/jniLibs/${ANDROID_ABI}/libnative-activity.so")
#        ADD_CUSTOM_COMMAND(TARGET ${TARGET} COMMAND ${CMAKE_COMMAND} -E copy_directory "${SILEXARS_PROJECT_PATH}/assets" "${SILEXARS_PATH}/third-party/android/LiveWallpaper/app/src/main/assets")
        ADD_CUSTOM_COMMAND(TARGET ${TARGET} COMMAND ${SILEXARS_PATH}/third-party/android/LiveWallpaper/gradlew -p ${SILEXARS_PATH}/third-party/android/LiveWallpaper/ ${ANDROID_BUILD_CMD})
        ADD_CUSTOM_COMMAND(TARGET ${TARGET} COMMAND ${ANDROID_SDK}/platform-tools/adb install -r ${SILEXARS_PATH}/third-party/android/LiveWallpaper/app/build/outputs/apk/app-${ANDROID_BUILD_TYPE}.apk)
    ELSE()
        ADD_SILEXARS_EXECUTABLE(${TARGET} ${ARGV})
    ENDIF()
ENDFUNCTION()

#SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -static -static-libgcc")
#SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static -static-libgcc -static-libstdc++")
ADD_DEFINITIONS(-std=c++11)
