//!Incomplete
//!Touch events not implemented yet

#include <Veritas/Definitions/Definitions.h>
#ifdef LINUX

#include <Veritas/Data/String.h>
#include <cstring>
#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <X11/XKBlib.h>
#include <X11/Xlocale.h>
#include <X11/extensions/XI2.h>
#include <cstdio>

#include "Window.h"
#include "GLContext.h"
#include "../Managers/Manager.h"

using namespace Silexars;
using namespace Data;
using namespace System;
using namespace Managers;
using namespace IO;
using namespace Devices;
using namespace Math;

using UI::Window;

struct LinuxWindow {
    ::Display* d;
    ::Window w;
    Atom wmDeleteMessage;
    XIM im;
    XIC ic;
};

void Window::systemCreateWindow(Window* parent, const char *name, uint32 w, uint32 h, int32 x, int32 y) {
    LinuxWindow* lw = new LinuxWindow;
    lw->d = (::Display*) Manager::getManager()->getDeviceManager()->getDisplayManager()->getDefaultDisplay()->id;
    lw->w = XCreateSimpleWindow(lw->d, RootWindow(lw->d,0), x, y, w, h, 0, BlackPixel(lw->d,0), WhitePixel(lw->d,0));

    XSelectInput(lw->d, lw->w, KeyPressMask | KeyReleaseMask | ButtonPressMask | ButtonReleaseMask | ButtonMotionMask | PointerMotionMask | StructureNotifyMask );
    XMapWindow(lw->d, lw->w);

    lw->wmDeleteMessage = XInternAtom(lw->d,"WM_DELETE_WINDOW",false);
    XSetWMProtocols(lw->d, lw->w, &lw->wmDeleteMessage,1);

    if (!setlocale(LC_ALL, "")) perror("setlocale");
    if (!XSupportsLocale()) perror("XSupportsLocale");
    if (!XSetLocaleModifiers("@im=none")) perror("XSetLocaleModifiers");

    lw->im = XOpenIM(lw->d, 0, 0, 0);
    if (!lw->im) perror("XOpenIM");

    lw->ic = XCreateIC(lw->im, XNInputStyle, XIMPreeditNothing | XIMStatusNothing, XNClientWindow, lw->w, NULL);
    if (!lw->ic) perror("XCreateIC");
    XSetICFocus(lw->ic);

    id = (Handle) lw;
}

void Window::systemSetName(const char *name) { XStoreName(((LinuxWindow*) id)->d,((LinuxWindow*) id)->w,name); }
void Window::systemSetPosition(int32 x, int32 y) {
    LinuxWindow *lw = (LinuxWindow*) id;
    int32 vx = systemGetViewX();
    int32 vy = systemGetViewY();
    XMoveWindow(lw->d, lw->w, x - vx, y - vy);
}
void Window::systemSetDimension(uint32 w, uint32 h) {
    LinuxWindow *lw = (LinuxWindow*) id;
    int32 vx = systemGetViewX();
    int32 vy = systemGetViewY();
    XResizeWindow(lw->d, lw->w, w - vx*2, h - vx - vy);
}

void Window::manage() {
    LinuxWindow* lw = (LinuxWindow*) id;
    ::Display *d = lw->d;
    while (XPending(d)) {
        XEvent e;
        XPeekEvent(d,&e);
        if (e.type == UnmapNotify || e.type == DestroyNotify) XNextEvent(d,&e); // if any Window was closed and is no longer listed, we can ignore their destruction events
        else if (e.xany.window == lw->w) {
            XNextEvent(d,&e);
            if (XFilterEvent(&e, lw->w)) continue;

            switch (e.type) {
                case KeymapNotify: XRefreshKeyboardMapping(&e.xmapping); break;
                case Expose: if (e.xexpose.count == 0) /*runDraw();*/ break;
                case ConfigureNotify: {
                    int32 vx = systemGetViewX();
                    int32 vy = systemGetViewY();
                    int32 nx = e.xconfigure.x - vx;
                    int32 ny = e.xconfigure.y - vy;
                    uint32 nw = e.xconfigure.width + vx*2;
                    uint32 nh = e.xconfigure.height + vx + vy;

                    if (nw != w || nh != h) runResize(nw, nh);
                    if (nx != x || ny != y) runMove(nx, ny);
                }
                break;
                case FocusIn: runFocus(); break;
                case FocusOut: runBlur(); break;
                case ButtonPress:
                case MotionNotify:
                case ButtonRelease: {
                    Touchscreen::Touch *touch;
                    if (e.type == MotionNotify) {
                        if (!lmouse->isHovering()) touch = lmouse;
                        else if (!rmouse->isHovering()) touch = rmouse;
                        else touch = mmouse;
                        if (touch->isHovering()) runTouchHover(touch, vec2(e.xmotion.x, e.xmotion.y));
                        else runTouchMove(touch, vec2(e.xmotion.x, e.xmotion.y));
                    } else {
                        if (e.xbutton.button == 1) touch = lmouse;
                        else if (e.xbutton.button == 2) touch = mmouse;
                        else if (e.xbutton.button == 3) touch = rmouse;
                        else if (e.xbutton.button == 4) break; // scroll up
                        else if (e.xbutton.button == 5) break; // scroll down - if they don't break, they will access a non-allocated touch
                        if (e.type == ButtonRelease) runTouchEnd(touch, vec2(e.xmotion.x, e.xmotion.y));
                        else runTouchStart(touch, vec2(e.xmotion.x, e.xmotion.y));
                    }
                    break;
                }
                case KeyPress:
                case KeyRelease: {
                    bool shift = e.xkey.state & ShiftMask;
                    bool numlock = e.xkey.state & Mod2Mask;
                    bool capslock = e.xkey.state & LockMask;

                    uint32 keyCode = e.xkey.keycode;
                    if (e.type == KeyPress) {
                        KeySym keysym = 0;
                        Status status = 0;
                        char str[20];

                        int isPrintable = Xutf8LookupString(lw->ic, (XKeyPressedEvent*)&e, str, sizeof(str), &keysym, &status);
                        uint32 charCode = isPrintable ? String::getCharCodeFromUTF8(str) : 0;

                        runKeyStart(keyCode, charCode, shift, numlock, capslock);
                    } else runKeyEnd(keyCode, 0, shift, numlock, capslock);
                }
                case ClientMessage: if ((Atom) e.xclient.data.l[0] == lw->wmDeleteMessage) runClose(); break;
            }
        } else return;
    }
}

void Window::systemDestroyWindow() {
    LinuxWindow* lw = (LinuxWindow*) id;
    XDestroyWindow(lw->d, lw->w);
    XDestroyIC(lw->ic);
    XCloseIM(lw->im);

    delete lw;
}

void Window::setCursorVisibility(bool b) {
    if (b && !cursorVisibility) XUndefineCursor(((LinuxWindow*) id)->d,((LinuxWindow*) id)->w);
    else if (!b && cursorVisibility) {
        ::Display *display = ((LinuxWindow*) id)->d;
        ::Window window = ((LinuxWindow*) id)->w;

        XColor black = {0};
        static char noData[8] = {0};
        Pixmap bitmapNoData = XCreateBitmapFromData(display, window, noData, 8, 8);
        Cursor invisibleCursor = XCreatePixmapCursor(display, bitmapNoData, bitmapNoData, &black, &black, 0, 0);

        XDefineCursor(display,window, invisibleCursor);

        XFreePixmap(display,bitmapNoData);
        XFreeCursor(display, invisibleCursor);
    }
    cursorVisibility = b;
}

void Window::systemSetFullscreen(bool b) {
    ::Display *dpy = ((LinuxWindow*) id)->d;
    ::Window win = ((LinuxWindow*) id)->w;

    XEvent xev;
    Atom wm_state = XInternAtom(dpy, "_NET_WM_STATE", False);
    Atom fullscreen = XInternAtom(dpy, "_NET_WM_STATE_FULLSCREEN", False);

    memset(&xev, 0, sizeof(xev));
    xev.type = ClientMessage;
    xev.xclient.window = win;
    xev.xclient.message_type = wm_state;
    xev.xclient.format = 32;
    xev.xclient.data.l[0] = b;
    xev.xclient.data.l[1] = fullscreen;
    xev.xclient.data.l[2] = 0;

    XSendEvent(dpy, DefaultRootWindow(dpy), False, SubstructureNotifyMask, &xev);
}

int32 Window::systemGetViewX() {
    LinuxWindow* lw = (LinuxWindow*) id;
    XWindowAttributes xwa;
    do {
        XGetWindowAttributes(lw->d, lw->w, &xwa);
    } while (xwa.x < 0 || xwa.y < 0);
    return xwa.x;
}
int32 Window::systemGetViewY() {
    LinuxWindow* lw = (LinuxWindow*) id;
    XWindowAttributes xwa;
    do {
        XGetWindowAttributes(lw->d, lw->w, &xwa);
    } while (xwa.x < 0 || xwa.y < 0);
    return xwa.y;
}
uint32 Window::systemGetViewWidth() {
    LinuxWindow* lw = (LinuxWindow*) id;
    ::Window root;
    int x,y;
    unsigned int w,h,border,depth;
    XGetGeometry(lw->d, lw->w, &root, &x, &y, &w, &h, &border, &depth);
    return w;
}

uint32 Window::systemGetViewHeight() {
    LinuxWindow* lw = (LinuxWindow*) id;
    ::Window root;
    int x,y;
    unsigned int w,h,border,depth;
    XGetGeometry(lw->d, lw->w, &root, &x, &y, &w, &h, &border, &depth);
    return h;
}

#endif
