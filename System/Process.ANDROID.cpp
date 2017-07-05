#include <Veritas/Definitions/Definitions.h>
#ifdef ANDROID

#include <Veritas/System/System.h>

using namespace Silexars;
using namespace System;
using namespace Managers;

#include "third-party/android-naglue/android_native_app_glue.h"
#include <android/log.h>

#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, "native-activity", __VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN, "native-activity", __VA_ARGS__)

#include <EGL/egl.h>
#include <GLES2/gl2.h>

static Manager *manager;
static volatile Process* p = 0;

extern ANativeWindow* native_window;
extern AAssetManager* assetManager;

// process management have to be reworked.
static void onAppCmd(struct android_app* app, int32_t cmd) {
    switch (cmd) {
        case APP_CMD_INIT_WINDOW: if (app->window) {
            // implement on View::setFormat(RGB | RGBA) ANativeActivity_setWindowFormat(app->activity, WINDOW_FORMAT_RGBA_8888);
            native_window = app->window;
            manager = Manager::getManager();
            p = EntryPoint(0, 0);
            break;
        }
        case APP_CMD_TERM_WINDOW: delete p; p = 0; break;
        //case APP_CMD_GAINED_FOCUS: break;
        //case APP_CMD_LOST_FOCUS: break;
        case APP_CMD_PAUSE: if (p) ((Process*) p)->suspend(); break;
        case APP_CMD_RESUME: if (p) ((Process*) p)->resume(); break; // it will only be resumed on LiveWallpaper, because NativeActivity always destroy everything
    }
}

extern "C" void android_main(android_app *app) {
    if (!app) return; // used for avoiding stripping.
    app_dummy(); // Make sure glue isn't stripped.

    app->onAppCmd = onAppCmd;
    assetManager = app->activity->assetManager;

    while (1) {
        int ident;
        int events;
        struct android_poll_source* source;

        while ((ident=ALooper_pollAll(0, NULL, &events, (void**)&source)) >= 0) {
            if (source != NULL) source->process(app, source);

            if (app->destroyRequested) {
                delete p; p = 0;
                return;
            }
        }

        if (p) manager->manage();
    }
}


#endif // ANDROID
