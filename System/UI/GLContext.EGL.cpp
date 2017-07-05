#include <Veritas/Definitions/Definitions.h>
#ifdef EGL
#include "GLContext.h"

#include "../Managers/Manager.h"

#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <EGL/eglplatform.h>

#include <android/native_window.h>

using namespace Silexars;
using namespace System;
using namespace Managers;
using namespace UI;

static EGLDisplay eglDisplay;
extern EGLSurface eglSurface;
extern EGLContext eglContext;

#define EGL_CONTEXT_MINOR_VERSION_KHR 0x30FB

#include <GLES2/gl2.h>

//#error Implement with struct NativeGLContext

struct NativeGLContext {
    EGLDisplay display;
    EGLSurface surface;
    EGLContext context;
};

void GLContext::systemCreateGLContext(View *surface) {
    const EGLint attribs[] = {
        EGL_RED_SIZE, 8,
        EGL_GREEN_SIZE, 8,
        EGL_BLUE_SIZE, 8,
        EGL_ALPHA_SIZE, 8,
        EGL_NONE
    };
    EGLint dummy, format;
    EGLint numConfigs;
    EGLConfig config;
    EGLContext eglContext;

    EGLNativeWindowType window = (EGLNativeWindowType) surface->getWindow()->id;
    eglDisplay = (EGLDisplay) Manager::getManager()->getDeviceManager()->getDisplayManager()->getDefaultDisplay()->id;

    if (!eglChooseConfig(eglDisplay, attribs, &config, 1, &numConfigs));// LOGW("Unable to eglChooseConfig");
    if (!eglGetConfigAttrib(eglDisplay, config, EGL_NATIVE_VISUAL_ID, &format));// LOGW("Unable to eglGetConfigAttrib");

    ANativeWindow_setBuffersGeometry(window, 0, 0, format);

    eglSurface = eglCreateWindowSurface(eglDisplay, config, window, NULL);

    if (!eglSurface);// LOGW("Unable to eglCreateWindowSurface");

    const EGLint context_2_0[] = { EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE };
    eglContext = eglCreateContext(eglDisplay, config, NULL, context_2_0);
    id = (Handle) eglContext;

    if (!id);// LOGW("Unable to eglCreateContext");
}

void GLContext::systemDestroyGLContext() { eglDestroyContext(eglDisplay, (EGLContext) id); }
void GLContext::systemMakeCurrent() { eglMakeCurrent(eglDisplay, eglSurface, eglSurface, (EGLContext) id); }
void GLContext::systemNullCurrent() { eglMakeCurrent(eglDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT); }

void GLContext::swapBuffers() { eglSwapBuffers(eglDisplay, eglSurface); }

void* GLContext::getProcAddress(const char *name) { return (void*) eglGetProcAddress(name); }

#endif
