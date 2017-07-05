#include <Veritas/Definitions/Definitions.h>
#ifdef ANDROID
#include "Screen.h"
#include "../GraphicsDevice.h"

#include <android/native_window.h>

using namespace Silexars;
using namespace System::IO::Devices::Displays;

extern ANativeWindow* native_window;

void Screen::systemCreateScreen(GraphicsDevice *display, uint8 i) {
    strcpy(name, "Default Screen");
    id = display->id;
}
Screen::~Screen() {}

uint32 Screen::getWidth() const { return ANativeWindow_getWidth(native_window); }
uint32 Screen::getHeight() const { return ANativeWindow_getHeight(native_window); }

#endif
