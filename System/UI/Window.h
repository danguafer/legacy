//!Incomplete
//!Lacks events.
//!Lacks cursor move and grap // http://tronche.com/gui/x/xlib/input/XGrabPointer.html // http://tronche.com/gui/x/xlib/input/XWarpPointer.html

#ifndef SILEXARS_MANAGEMENT_UI_WINDOW_H_
#define SILEXARS_MANAGEMENT_UI_WINDOW_H_

#include <Veritas/Definitions/Definitions.h>
#include "../IO/Devices/GraphicsDevice.h"
#include "../IO/Devices/Keyboard.h"
#include "../IO/Devices/Touchscreen.h"
#include "View.h"
#include "../IO/Message.h"

namespace Silexars {
    namespace System {
        namespace Managers { class WindowManager; }
        namespace UI {
            class Window : public IO::Message::Listener {
                public:
                    Window(Window *parent, const char *name = "", uint32 surfaceWidth = 800, uint32 surfaceHeight = 600, int32 x = CENTER, int32 y = CENTER);
                    Window(const char *name = "", uint32 surfaceWidth = 800, uint32 surfaceHeight = 600, int32 x = CENTER, int32 y = CENTER);
                    ~Window();

                    bool isOpen() const;

                    void setFullscreen(bool b);
                    bool isFullscreen() const;

                    void setName(const char* name);
                    const char* getName() const;

                    void setPosition(int32 x, int32 y);
                    int32 getX() const;
                    int32 getY() const;

                    void setDimension(uint32 w, uint32 h);
                    uint32 getWidth() const;
                    uint32 getHeight() const;

                    void setCursorVisibility(bool b);
                    bool getCursorVisibility() const;

                    View* getView() const;

                    /*
                     * KeyStart
                     * KeyEnd
                     *
                     * TouchHover
                     * TouchStart
                     * TouchMove
                     * TouchEnd
                     *
                     * Move
                     * Resize
                     *
                     * Focus
                     * Blur
                     * Close
                     */

                    enum { CENTER = 2147483647 };
                protected:
                    friend class Managers::WindowManager;
                    friend class GLContext;
                    friend class View;

                    void CWindow(Window *parent, const char *name, uint32 w, uint32 h, int32 x, int32 y);
                    void close();

                    void manage();

                    void runResize(uint32 w, uint32 h);
                    void runMove(int32 x, int32 y);

                    void runBlur();
                    void runFocus();
                    void runClose();

                    void runKeyStart(uint32 key, uint32 charCode, bool shift, bool numlock, bool capslock);
                    void runKeyEnd(uint32 key, uint32 charCode, bool shift, bool numlock, bool capslock);

                    void runTouchStart(IO::Devices::Touchscreen::Touch *touch, const Math::vec2& position);
                    void runTouchMove(IO::Devices::Touchscreen::Touch *touch, const Math::vec2& position);
                    void runTouchEnd(IO::Devices::Touchscreen::Touch *touch, const Math::vec2& position);
                    void runTouchHover(IO::Devices::Touchscreen::Touch *touch, const Math::vec2& position);

                    static IO::Devices::Touchscreen::Touch *lmouse, *mmouse, *rmouse;
                    Window *parent;
                    View *view;
                    Handle id;

                    bool cursorVisibility;

                    bool isfullscreen, isopen;
                    int32 x,y,x0,y0;
                    uint32 w,h,w0,h0;

                    char name[64];

                    void systemCreateWindow(Window *parent, const char *name, uint32 w, uint32 h, int32 x, int32 y);
                    void systemSetName(const char* name);
                    void systemSetPosition(int32 x, int32 y);
                    void systemSetDimension(uint32 w, uint32 h);
                    void systemDestroyWindow();
                    void systemSetFullscreen(bool b);
                    int32 systemGetViewX();
                    int32 systemGetViewY();
                    uint32 systemGetViewWidth();
                    uint32 systemGetViewHeight();
            };
        }
    }
}

#endif
