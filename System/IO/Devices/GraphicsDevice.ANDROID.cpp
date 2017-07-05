#include <Veritas/Definitions/Definitions.h>
#ifdef ANDROID
#include "GraphicsDevice.h"
#include <EGL/egl.h>

using namespace Silexars::System::IO::Devices;

void GraphicsDevice::systemCreateDisplay(const char *name, uint8 type) {
    id = (Handle) eglGetDisplay(EGL_DEFAULT_DISPLAY);
    eglInitialize((EGLDisplay) id, 0, 0);
    displays.push_back(new Displays::Screen(this, 0));
}

void GraphicsDevice::systemDestroyDisplay() { if (id) eglTerminate((EGLDisplay) id); }

#endif
