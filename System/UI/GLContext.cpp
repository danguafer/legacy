//!Complete

#include "GLContext.h"
#include "Window.h"

using namespace Silexars;
using namespace System;
using namespace UI;

GLContext* GLContext::current = 0;

#ifdef ANDROID
    #include <GLES/gl.h>
#else
    #include <GL/gl.h>
    #include <GL/glext.h>
#endif

GLContext::GLContext(View* view) {
    this->view = view;
    id = 0;
    systemCreateGLContext(view);

    #ifndef OPENGLES
    GLContext* previous = getCurrent();
    makeCurrent();

    GLint glmajor, glminor;
    glGetIntegerv(GL_MAJOR_VERSION, &glmajor);
    glGetIntegerv(GL_MINOR_VERSION, &glminor);

    major = glmajor;
    minor = glminor;

    if (previous) previous->makeCurrent();
    else nullCurrent();
    #endif
}

GLContext::~GLContext() {
    systemDestroyGLContext();
    if (current == this) nullCurrent();
}

void GLContext::makeCurrent() {
    if (current != this) {
        systemMakeCurrent();
        current = this;
    }
}
void GLContext::nullCurrent() {
    if (current) {
        systemNullCurrent();
        current = 0;
    }
}


View* GLContext::getView() const { return view; }

GLContext* GLContext::getCurrent() { return current; }

bool GLContext::isES() const {
    #ifdef OPENGLES
    return true;
    #else
    return false;
    #endif
}

uint32 GLContext::getMajorVersion() const { return major; }
uint32 GLContext::getMinorVersion() const { return minor; }
