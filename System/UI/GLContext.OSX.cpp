#include <Veritas/Definitions/Definitions.h>
#ifdef OSX
#include "GLContext.h"

#include <GLUT/glut.h>

using namespace Silexars::System::UI;

void GLContext::systemCreateGLContext(View *surface) {}
void GLContext::systemDestroyGLContext() {}
void GLContext::systemMakeCurrent() {}
void GLContext::systemNullCurrent() { }
void GLContext::swapBuffers() { glutSwapBuffers(); }

#endif
