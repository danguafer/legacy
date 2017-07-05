#include <Veritas/Definitions/Definitions.h>
#ifdef ANDROID
#include "Window.h"

#include <android/native_window.h>
ANativeWindow *native_window = 0;

using namespace Silexars::System::UI;

void Window::manage() {}

void Window::systemCreateWindow(Window *parent, const char *name, uint32 w, uint32 h, int32 x, int32 y) { this->id = (Handle) native_window; }
void Window::systemDestroyWindow() {}
uint32 Window::systemGetViewWidth() { return 0; }
uint32 Window::systemGetViewHeight() { return 0; }
int32 Window::systemGetViewX() { return 0; }
int32 Window::systemGetViewY() { return 0; }
void Window::systemSetFullscreen(bool b) {}
void Window::systemSetDimension(uint32 w, uint32 h) {}
void Window::systemSetName(const char *name) {}
void Window::systemSetPosition(int32 x, int32 y) {}

#endif
