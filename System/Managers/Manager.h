//!Complete

#ifndef SILEXARS_SYSTEM_MANAGERS_MANAGER_H_
#define SILEXARS_SYSTEM_MANAGERS_MANAGER_H_

#include "DeviceManager.h"
#include "WindowManager.h"
#include "ProcessManager.h"

namespace Silexars {
    namespace System {
        namespace Managers {
            class Manager {
                public:
                    static Manager* getManager();

                    DeviceManager *getDeviceManager() const;
                    WindowManager *getWindowManager() const;
                    ProcessManager *getProcessManager() const;

                    void manage();
                private:
                    Manager();
                    ~Manager();

                    DeviceManager deviceManager;
                    WindowManager windowManager;
                    ProcessManager processManager;
            };
        }
    }
}

#endif
