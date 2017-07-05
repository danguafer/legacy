//!Complete

#include <Veritas/Definitions/Definitions.h>
#ifdef WINDOWS
#include "GLContext.h"
#include "Window.h"
#include "View.h"

#include <windows.h>

using namespace Silexars;
using namespace System;
using namespace UI;

struct WindowGLContext {
    HDC hdc;
    HGLRC hrc;
};

void GLContext::systemCreateGLContext(View* view) {
    static PIXELFORMATDESCRIPTOR pfd = {
       sizeof(pfd),
       1,
       PFD_DRAW_TO_WINDOW|PFD_SUPPORT_OPENGL|PFD_DOUBLEBUFFER,
       PFD_TYPE_RGBA,
       32,0,0,0,0,0,0,
       0,0,0,0,0,0,0,
       32,0,0,
       PFD_MAIN_PLANE,0,0,0,0};

    WindowGLContext* wgl = new WindowGLContext;

    wgl->hdc = GetDC((HWND) view->getWindow()->id);
    SetPixelFormat(wgl->hdc,ChoosePixelFormat(wgl->hdc,&pfd),&pfd);
    wgl->hrc = wglCreateContext(wgl->hdc);

    id = (Handle) wgl;
}

void GLContext::systemDestroyGLContext() { wglDeleteContext(((WindowGLContext*) id)->hrc); }

void GLContext::systemMakeCurrent() {
    WindowGLContext *wgl = (WindowGLContext*) id;
    wglMakeCurrent(wgl->hdc, wgl->hrc);
}
void GLContext::systemNullCurrent() { wglMakeCurrent(0,0); }

void GLContext::swapBuffers() { SwapBuffers(((WindowGLContext*) id)->hdc); }

void* GLContext::getProcAddress(const char* name) { return (void*) wglGetProcAddress(name); }

#endif
