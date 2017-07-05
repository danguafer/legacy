//!Complete

#include "View.h"
#include "Window.h"

using namespace Silexars;
using namespace System;
using namespace UI;

View::View(Window *window) {
    this->window = window;
    glctx = 0;
}

View::~View() { delete glctx; }

void View::setDimension(uint32 w, uint32 h) {
    runResize(w, h);
    systemSetDimension(w, h);
}

Window* View::getWindow() const { return window; }
GLContext* View::getGLContext() const {
    if (!glctx) const_cast<View*>(this)->glctx = new GLContext(const_cast<View*>(this));
    return glctx;
}

void View::setPixelFormat(uint32 PIXELFORMAT) {
    //systemSetPixelFormat(PIXELFORMAT);
    this->pixelFormat = PIXELFORMAT;
}

uint32 View::getPixelFormat() const { return pixelFormat; }

void View::runMove(int32 x, int32 y) {
    this->x = x;
    this->y = y;
}

void View::runResize(uint32 w, uint32 h) {
    this->w = w;
    this->h = h;
}

int32 View::getX() const { return x; }
int32 View::getY() const { return y; }
uint32 View::getWidth() const { return w; }
uint32 View::getHeight() const { return h; }
