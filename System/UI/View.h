//!Complete

#ifndef SILEXARS_SYSTEM_UI_VIEW_H_
#define SILEXARS_SYSTEM_UI_VIEW_H_

#include <Veritas/Definitions/Definitions.h>
#include "GLContext.h"

namespace Silexars {
    namespace System {
        namespace UI {
            class Window;
            class View {
                public:
                    Window* getWindow() const;

                    void setDimension(uint32 w, uint32 h);

                    uint32 getWidth() const;
                    uint32 getHeight() const;
                    int32 getX() const;
                    int32 getY() const;

                    GLContext* getGLContext() const;

                    void setPixelFormat(uint32 PIXELFORMAT);
                    uint32 getPixelFormat() const;
                    enum PIXELFORMATS { UNKNOWN, RGB888, RGBA8888, RGBX8888 };
                private:
                    friend class Window;
                    View(Window *window);
                    ~View();

                    uint32 pixelFormat;

                    void systemSetDimension(uint32 w, uint32 h);

                    void runMove(int32 x, int32 y);
                    void runResize(uint32 x, uint32 y);

                    Handle id; // not used yet

                    int32 x,y;
                    uint32 w,h;                    

                    Window* window;
                    GLContext* glctx;
            };
        }
    }
}

#endif
