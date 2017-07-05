//!Complete

#include <Veritas/Definitions/Definitions.h>
#ifdef LINUX

#include "View.h"
#include "Window.h"

#include <X11/Xlib.h>
#include <X11/Xatom.h>

using namespace Silexars;
using namespace System;
using namespace UI;

struct LinuxWindow {
    ::Display* d;
    ::Window w;
    Atom wmDeleteMessage;
};

void View::systemSetDimension(uint32 w, uint32 h) {
    Window *window = getWindow();
    LinuxWindow* lw = (LinuxWindow*) window->id;

    int32 x = window->systemGetViewX();
    int32 y = window->systemGetViewY();
    window->setDimension(w + x*2, h + x + y);
}

#endif
