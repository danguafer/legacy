//!Complete

#ifndef SILEXARS_SYSTEM_UI_GLCONTEXT_H_
#define SILEXARS_SYSTEM_UI_GLCONTEXT_H_

#include <Veritas/Definitions/Definitions.h>

namespace Silexars {
    namespace System {

        namespace UI {
            class View;
            class GLContext {
                public:
                    static GLContext *getCurrent();

                    static void nullCurrent();
                    void makeCurrent();
                    void swapBuffers();

                    View* getView() const;

                    bool isES() const;
                    uint32 getMajorVersion() const;
                    uint32 getMinorVersion() const;

                    static void* getProcAddress(const char* name);
                private:
                    GLContext(View *view);
                    ~GLContext();

                    static void systemNullCurrent();
                    void systemCreateGLContext(View *view);
                    void systemDestroyGLContext();
                    void systemMakeCurrent();

                    friend class Window;
                    friend class View;
                    static GLContext *current;
                    View *view;
                    Handle id;

                    uint32 major, minor;
            };
        }
    }
}

#endif
