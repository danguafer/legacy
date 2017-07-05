//!Complete

#include <Veritas/Definitions/Definitions.h>
#ifdef LINUX
#include "GLContext.h"
#include "Window.h"

#include <GL/glx.h>

using namespace Silexars;
using namespace System;
using namespace UI;

struct LinuxWindow {
    ::Display* d;
    ::Window w;
    Atom wmDeleteMessage;
};

void GLContext::systemCreateGLContext(View *view) {
    ::Display* display = ((LinuxWindow*) view->getWindow()->id)->d;
    GLint att[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None };
    XVisualInfo *vi = glXChooseVisual(display,0,att);
    id = (Handle) glXCreateContext(display, vi, 0, GL_TRUE);
}

void GLContext::systemDestroyGLContext() { glXDestroyContext(((LinuxWindow*) view->getWindow()->id)->d, (GLXContext) id); }
void GLContext::systemMakeCurrent() { glXMakeCurrent(((LinuxWindow*) view->getWindow()->id)->d,((LinuxWindow*) view->getWindow()->id)->w,(GLXContext) id); }
void GLContext::systemNullCurrent() { glXMakeCurrent(((LinuxWindow*) current->view->getWindow()->id)->d,0,0); }

void GLContext::swapBuffers() { glXSwapBuffers(((LinuxWindow*) view->getWindow()->id)->d, ((LinuxWindow*) view->getWindow()->id)->w); }

void* GLContext::getProcAddress(const char* name) { return (void*) glXGetProcAddress((const GLubyte*) name); }

#endif
