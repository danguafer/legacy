#ifndef SILEXARS_DEFINITIONS_OS_H
#define SILEXARS_DEFINITIONS_OS_H

#if defined(_WIN32) || defined(_WIN64)
    #define WINDOWS WINDOWS
    #define TARGET WINDOWS
#elif __APPLE__
    #include "TargetConditionals.h"
    #if TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR
        #define IOS IOS
        #define TARGET IOS
    #elif TARGET_OS_MAC
        #define OSX OSX
        #define TARGET OSX
    #endif
#elif defined(__ANDROID__)
    #ifndef ANDROID
                #define ANDROID ANDROID
                #define TARGET ANDROID
        #endif
#elif defined(EMSCRIPTEN)
    #define TARGET EMSCRIPTEN
#elif defined(__linux)
    #define LINUX LINUX
    #define TARGET LINUX
#endif

#ifdef __unix
    #define UNIX
#endif

#if defined(ANDROID) || defined(IOS)
    #define MOBILE
#elif defined(WINDOWS) || defined(OSX) || defined(LINUX)
    #define DESKTOP
#elif defined(JAVASCRIPT)
    #define BROWSER
#endif

#if defined(LINUX) || defined(OSX) || defined(ANDROID)
    #define POSIX
#endif

#if defined(MOBILE) || defined(BROWSER)
    #define OPENGLES
    #define EGL
    #if ANDROID_NATIVE_API_LEVEL >= 18
        #define OPENGLES3
    #endif
    #if ANDROID_NATIVE_API_LEVEL >= 21
        #define OPENGLES31
    #endif
#else
    #define OPENGL
#endif

#endif // OS_H
