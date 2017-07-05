#include <Silexars/Definitions/Definitions.h>
#ifdef OSX
#include "Window.h"

#include <GLUT/glut.h>

using namespace Silexars::System::UI;

void Window::manage() {}

void Window::systemCreateWindow(Window *parent, const char *name, uint32 w, uint32 h, int32 x, int32 y) {
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(x, y);
    glutInitWindowSize(w, h);
    glutCreateWindow(name);
}
void Window::systemDestroyWindow() {}
uint32 Window::systemGetViewHeight() {}
uint32 Window::systemGetViewWidth() {}
int32 Window::systemGetViewX() {}
int32 Window::systemGetViewY() {}
void Window::systemSetDimension(uint32 w, uint32 h) {}
void Window::systemSetFullscreen(bool b) {}
void Window::systemSetName(const char *name) {}
void Window::systemSetPosition(int32 x, int32 y) {}

#endif
