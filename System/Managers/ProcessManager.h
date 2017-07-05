//!Complete

#ifndef SILEXARS_SYSTEM_MANAGERS_PROCESSMANAGER_H_
#define SILEXARS_SYSTEM_MANAGERS_PROCESSMANAGER_H_

#include <Veritas/Definitions/Definitions.h>
#include "../Process.h"
#include <list>

namespace Silexars {
    namespace System {
        namespace Managers {
            class Manager;
            class ProcessManager {
                private:
                    typedef std::list<System::Process*> List;
                public:
                    typedef List::iterator iterator;

                    iterator begin();
                    iterator end();
                    uint32 size() const;
                private:
                    friend class Manager;
                    friend class System::Process;

                    List processes;
                    void manage();

                    ProcessManager();
            };
        }
    }
}

#endif
