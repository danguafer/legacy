//!Complete

#include <Veritas/Definitions/Definitions.h>
#ifdef WINDOWS

#include "View.h"
#include "Window.h"
#include <windows.h>

using namespace Silexars;
using namespace System;
using namespace UI;

void View::systemSetDimension(uint32 w, uint32 h) {
    Window* window = getWindow();

    RECT r;
    r.left = 0;
    r.top = 0;
    r.right = w;
    r.bottom = h;

    AdjustWindowRectEx(&r, GetWindowLong((HWND) window->id, GWL_STYLE), 0, GetWindowLong((HWND) window->id, GWL_EXSTYLE));

    uint32 ww = r.right - r.left;
    uint32 wh = r.bottom - r.top;
    window->setDimension(ww, wh);
}

#endif // WINDOWS
