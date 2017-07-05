//!Incomplete
//!WM_DISPLAYCHANGE not implemented yet
//!Touch events not implemented yet
//!WM_UNICHAR not implemented yet

#define _WIN32_WINNT 0x601
#include <Veritas/Definitions/Definitions.h>
#ifdef WINDOWS

#include <cstring>
#include <windows.h>
#include <windowsx.h>

#include "../Managers/Manager.h"
#include "Window.h"
#include "GLContext.h"

using namespace Silexars;
using namespace System;
using namespace Managers;
using namespace IO;
using namespace Devices;
using namespace Displays;
using namespace UI;
using namespace Math;

#define MOUSEEVENTF_FROMTOUCH 0xFF515700

class WWindow : public Window {
    public:
        static LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
            WWindow *w = (WWindow*) GetWindowLongPtr(hwnd,GWLP_USERDATA);
            if (w && w->getView()) switch (msg) { // Only receive message after WM_CREATE is sent
                case WM_DESTROY: w->runClose(); break;
                case WM_SETFOCUS: w->runFocus(); break;
                case WM_KILLFOCUS: w->runBlur(); break;
                case WM_MOVE: {
                    RECT rect;
                    GetWindowRect((HWND) w->id,&rect);
                    w->runMove(rect.left, rect.top);
                    break;
                }
                case WM_SIZE: {
                    RECT rect;
                    GetWindowRect((HWND) w->id,&rect);
                    w->runResize(rect.right - rect.left, rect.bottom - rect.top);
                    break;
                }
                case WM_KEYDOWN:
                case WM_SYSKEYDOWN: if (lParam & 0x40000000) break; // key-repeat
                case WM_KEYUP:
                case WM_SYSKEYUP: {
                    uint32 key = wParam;
                    uint32 scancode = (lParam & 0x00FF0000) >> 16;
                    bool extended   = (lParam & 0x01000000);

                    if (key == VK_SHIFT) key = MapVirtualKey(scancode, 3);
                    if (extended) switch (key) {
                        case VK_CONTROL: key = VK_RCONTROL; break;
                        case VK_MENU: key = VK_RMENU; break;
                        case VK_RETURN: key = 232; break;
                    } else switch (key) {
                        case VK_DOWN: key = VK_NUMPAD2; break;
                        case VK_LEFT: key = VK_NUMPAD4; break;
                        case VK_RIGHT: key = VK_NUMPAD6; break;
                        case VK_UP: key = VK_NUMPAD8; break;
                        case VK_CLEAR: key = VK_NUMPAD5; break;
                        case VK_DELETE: key = VK_DECIMAL; break;
                        case VK_PRIOR: key = VK_NUMPAD9; break;
                        case VK_NEXT: key = VK_NUMPAD3; break;
                        case VK_INSERT: key = VK_NUMPAD0; break;
                        case VK_END: key = VK_NUMPAD1; break;
                        case VK_HOME: key = VK_NUMPAD7; break;
                    }

                    bool shift = GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT);
                    bool capslock = GetAsyncKeyState(VK_CAPITAL);
                    bool numlock = GetAsyncKeyState(VK_NUMLOCK);

                    uint32 charCode;
                    MSG charMSG;
                    PeekMessage(&charMSG, (HWND)w->id, 0, 0, PM_NOREMOVE);
                    if (charMSG.message == WM_CHAR) {
                        charCode = charMSG.wParam;
                    } else charCode = 0;

                    if (msg == WM_KEYDOWN || msg == WM_SYSKEYDOWN) w->runKeyStart(key, charCode, shift, numlock, capslock);
                    else w->runKeyEnd(key, charCode, shift, numlock, capslock);
                    break;
                }
                case WM_DISPLAYCHANGE: break; // for updating DisplayManager
            }
            return DefWindowProc(hwnd,msg,wParam,lParam);
        }
};

void Window::systemCreateWindow(Window *parent, const char *name, uint32 w, uint32 h, int32 x, int32 y) {
    static char szClassName[1024];
    GetModuleFileName(0,szClassName,1024);
    WNDCLASSEX wincl;
    wincl.hInstance = GetModuleHandle(0);
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WWindow::WindowProc;
    wincl.style = 0;
    wincl.cbSize = sizeof(WNDCLASSEX);
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;
    wincl.cbClsExtra = 0;
    wincl.cbWndExtra = 0;
    wincl.hbrBackground = (HBRUSH) COLOR_WINDOW;

    RegisterClassEx(&wincl);
    id = (Handle) CreateWindowEx(0,szClassName,name,WS_OVERLAPPEDWINDOW,x,y,w,h,parent ? (HWND) parent->id: HWND_DESKTOP,NULL,GetModuleHandle(0),NULL);
    SetWindowLongPtr((HWND) id,GWLP_USERDATA,(LONG_PTR)this);

    RegisterTouchWindow((HWND) id,0);
    SetProp((HWND) id, "MicrosoftTabletPenServiceProperty", (HANDLE)1);

    ShowWindow((HWND) id, SW_SHOW);
}

void Window::systemDestroyWindow() { DestroyWindow((HWND) id); }

void Window::systemSetName(const char *name) { SetWindowText((HWND)id,name); }

void Window::manage() {
    MSG msg;
    while (PeekMessage(&msg, (HWND)id, 0, 0, PM_REMOVE) > 0) {
        switch (msg.message) { // Friendship is really problematic, isn't it?
            case WM_LBUTTONDOWN:
            case WM_MBUTTONDOWN:
            case WM_RBUTTONDOWN:
            case WM_LBUTTONUP:
            case WM_MBUTTONUP:
            case WM_RBUTTONUP:
            case WM_MOUSEMOVE: if (!(GetMessageExtraInfo() & MOUSEEVENTF_FROMTOUCH)) {
                Touchscreen::Touch *touch;
                if (msg.message == WM_MOUSEMOVE) {
                    if (!lmouse->isHovering()) touch = lmouse;
                    else if (!rmouse->isHovering()) touch = rmouse;
                    else touch = mmouse;
                    if (touch->isHovering()) runTouchHover(touch, vec2(GET_X_LPARAM(msg.lParam), GET_Y_LPARAM(msg.lParam)));
                    else runTouchMove(touch, vec2(GET_X_LPARAM(msg.lParam), GET_Y_LPARAM(msg.lParam)));
                } else {
                    if (msg.message == WM_LBUTTONDOWN || msg.message == WM_LBUTTONUP) touch = lmouse;
                    else if (msg.message == WM_MBUTTONDOWN || msg.message == WM_MBUTTONUP) touch = mmouse;
                    else if (msg.message == WM_RBUTTONDOWN || msg.message == WM_RBUTTONUP) touch = rmouse;
                    if (msg.message == WM_LBUTTONDOWN || msg.message == WM_MBUTTONDOWN || msg.message == WM_RBUTTONDOWN) runTouchStart(touch, vec2(GET_X_LPARAM(msg.lParam), GET_Y_LPARAM(msg.lParam)));
                    else runTouchEnd(touch, vec2(GET_X_LPARAM(msg.lParam), GET_Y_LPARAM(msg.lParam)));
                }
                break;
            }
        }

        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

void Window::systemSetPosition(int32 x, int32 y) {
    SetWindowPos((HWND)id,0,x,y,0,0,SWP_NOSIZE | SWP_NOZORDER);
}

void Window::systemSetDimension(uint32 w, uint32 h) { SetWindowPos((HWND)id,0,0,0,w,h,SWP_NOMOVE | SWP_NOZORDER); }

void Window::systemSetFullscreen(bool b) {
    HWND hwnd = (HWND) id;
    Screen *s = Manager::getManager()->getDeviceManager()->getDisplayManager()->getDefaultDisplay()->getDefaultScreen();
    uint32 fullscreenWidth = s->getWidth();
    uint32 fullscreenHeight = s->getHeight();
    if (b) {
        SetWindowLongPtr(hwnd, GWL_EXSTYLE, WS_EX_APPWINDOW | WS_EX_TOPMOST);
        SetWindowLongPtr(hwnd, GWL_STYLE, WS_POPUP | WS_VISIBLE);
        SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, fullscreenWidth, fullscreenHeight, SWP_SHOWWINDOW);
        ShowWindow(hwnd, SW_MAXIMIZE);
    } else {
        SetWindowLongPtr(hwnd, GWL_STYLE, WS_OVERLAPPEDWINDOW | (GetWindowLong(hwnd, GWL_STYLE)&~WS_POPUP));
        SetWindowPos(hwnd, HWND_TOPMOST, x0, y0, w0, h0, SWP_SHOWWINDOW);
    }
}

uint32 Window::systemGetViewWidth() {
    RECT r;
    GetClientRect((HWND) id, &r);
    return r.right;
}

uint32 Window::systemGetViewHeight() {
    RECT r;
    GetClientRect((HWND) id, &r);
    return r.bottom;
}

int32 Window::systemGetViewX() {
    POINT point = {0};
    ClientToScreen((HWND) id, &point);
    return point.x;
}

int32 Window::systemGetViewY() {
    POINT point = {0};
    ClientToScreen((HWND) id, &point);
    return point.y;
}

#endif
