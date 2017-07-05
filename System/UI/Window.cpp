//!Complete

#include "Window.h"
#include "GLContext.h"
#include "../Managers/Manager.h"
#include <cstring>

using namespace Silexars;
using namespace System;
using namespace Managers;
using namespace UI;
using namespace IO;
using namespace Devices;
using namespace Displays;
using namespace Math;

Touchscreen::Touch *Window::lmouse = 0,
                   *Window::mmouse = 0,
                   *Window::rmouse = 0;

Window::Window(const char *name, uint32 w, uint32 h, int32 x, int32 y) { CWindow(0, name, w, h, x, y); }
Window::Window(Window *parent, const char *name, uint32 w, uint32 h, int32 x, int32 y) { CWindow(parent,name,w,h,x,y); }
void Window::CWindow(Window *parent, const char *name, uint32 w, uint32 h, int32 x, int32 y) {
    if (!Manager::getManager()->getWindowManager()->size()) {
        lmouse = new Touchscreen::Touch(vec2(0.0), Touchscreen::LMOUSE, true);
        mmouse = new Touchscreen::Touch(vec2(0.0), Touchscreen::MMOUSE, true);
        rmouse = new Touchscreen::Touch(vec2(0.0), Touchscreen::RMOUSE, true);
    }

    this->parent = parent;
    view = 0;

    cursorVisibility = true;
    isfullscreen = false;

    systemCreateWindow(parent, name, w, h, x, y);

    Manager::getManager()->getWindowManager()->windows.push_back(this);
    view = new View(this);

    view->setDimension(w,h);
    setPosition(x,y);
    setName(name);

    isopen = true;
}

Window::~Window() { close(); }

void Window::close() {
    if (isOpen()) {
        isopen = false;
        runClose();

        if (Manager::getManager()->getWindowManager()->size() == 1) {
            delete lmouse;
            delete mmouse;
            delete rmouse;
        }

        delete view;
        systemDestroyWindow();

        Manager::getManager()->getWindowManager()->windows.remove(this);
        id = 0;
    }
}

void Window::setFullscreen(bool b) {
    if (isfullscreen^b) {
        isfullscreen = b;
        systemSetFullscreen(b);

        if (b) {
            Screen* screen = Manager::getManager()->getDeviceManager()->getDisplayManager()->getDefaultDisplay()->getDefaultScreen();
            x0 = x;
            y0 = y;
            w0 = w;
            h0 = h;
            runResize(screen->getWidth(), screen->getHeight());
            view->runResize(screen->getWidth(), screen->getHeight());
            runMove(0, 0);
        } else {
            runResize(w0, h0);
            runMove(x0, y0);
        }
    }
}

bool Window::isFullscreen() const { return isfullscreen; }

void Window::setName(const char *name) {
    strncpy(this->name,name,sizeof(this->name)-1);
    this->name[sizeof(this->name)-1] = 0;
    systemSetName(this->name);
}
const char* Window::getName() const { return name; }

bool Window::isOpen() const { return isopen; }

void Window::setPosition(int32 x, int32 y) {
    if (!isFullscreen()) {
        Screen* screen = Manager::getManager()->getDeviceManager()->getDisplayManager()->getDefaultDisplay()->getDefaultScreen();

        if (x == CENTER) x = ((int32) screen->getWidth() - (int32) getWidth())/2;
        if (y == CENTER) y = ((int32) screen->getHeight() - (int32) getHeight())/2;

        systemSetPosition(x, y);
        runMove(x, y);
    }
}
int32 Window::getX() const { return x; }
int32 Window::getY() const { return y; }

void Window::setDimension(uint32 w, uint32 h) {
    if (!isFullscreen()) {
        systemSetDimension(w,h);
        runResize(w,h);
    }
}
uint32 Window::getWidth() const { return w; }
uint32 Window::getHeight() const { return h; }

bool Window::getCursorVisibility() const { return cursorVisibility; }

View* Window::getView() const { return view; }

void Window::runClose() {
    if (isOpen()) {
        Message().dispatch(this, "Close");
        close();
    }
}
void Window::runFocus() { Message().dispatch(this, "Focus"); }
void Window::runBlur() { Message().dispatch(this, "Blur"); }
void Window::runMove(int32 x, int32 y) {
    this->x = x;
    this->y = y;
    view->runMove(systemGetViewX(), systemGetViewY());
    Message().dispatch(this, "Move");
}

void Window::runResize(uint32 w, uint32 h) {
    this->w = w;
    this->h = h;
    view->runResize(systemGetViewWidth(), systemGetViewHeight());
    Message().dispatch(this, "Resize");
}

void Window::runKeyStart(uint32 syskey, uint32 charCode, bool shift, bool numlock, bool capslock) {
    uint32 key = Keyboard::systemToKey(syskey);
    Keyboard::pressmap[key] = true;

    Message().set("KeyCode", (void*) key).set("CharCode", (void*) charCode).dispatch(this, "KeyStart");
}
void Window::runKeyEnd(uint32 syskey, uint32 charCode, bool shift, bool numlock, bool capslock) {
    uint32 key = Keyboard::systemToKey(syskey);
    Keyboard::pressmap[key] = false;
    Message().set("KeyCode", (void*) key).set("CharCode", (void*) charCode).dispatch(this, "KeyEnd");
}
void Window::runTouchStart(Touchscreen::Touch *touch, const vec2 &position) {
    touch->ishovering = false;
    touch->start(position);
    Message().set("Touch", touch).dispatch(this, "TouchStart");
    runTouchMove(touch, position);
}
void Window::runTouchMove(Touchscreen::Touch *touch, const vec2 &position) {
    touch->move(position);
    Message().set("Touch", touch).dispatch(this, "TouchMove");
}
void Window::runTouchEnd(Touchscreen::Touch *touch, const vec2& position) {
    runTouchMove(touch, position);
    touch->ishovering = true;
    Message().set("Touch", touch).dispatch(this, "TouchEnd");
}
void Window::runTouchHover(Touchscreen::Touch *touch, const vec2 &position) {
    Message().set("Touch", touch).dispatch(this, "TouchHover");
}
