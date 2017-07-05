//!Complete

#ifndef SILEXARS_SYSTEM_PROCESS_H_
#define SILEXARS_SYSTEM_PROCESS_H_

#include <Veritas/Definitions/Definitions.h>
#include "Thread.h"
#include <new>
#include <list>

namespace Silexars { namespace System { class Process; } }
Silexars::System::Process* EntryPoint(int argc, char **argv);
#define SET_ENTRY_POINT(Main) Silexars::System::Process* EntryPoint(int argc, char **argv) { \
    Main* m = (Main*) operator new(sizeof(Main)); \
    m->argc = argc; m->argv = argv; \
    new(m)Main(); \
    return m; \
}

namespace Silexars {
    namespace System {
        namespace Managers { class ProcessManager; }
        class Process {
            private:
                typedef std::list<Thread> ThreadList;
            public:
                typedef ThreadList::iterator iterator;

                virtual ~Process();

                iterator begin() const;
                iterator end() const;
                uint32 size() const;

                uint32 getArgc() const;
                const char** getArgv() const;

                static bool isAdmin();

                virtual void onSuspend();
                virtual void onResume();

                void suspend();
                void resume();

                uint8 getStatus() const;
                enum STATUS { SUSPENDED, RUNNING };
            protected:
                Process();
                virtual void run();
            private:
                ThreadList threadList;

                uint32 argc;
                char **argv;

                uint8 status;

                friend class Managers::ProcessManager;
                friend System::Process* ::EntryPoint(int argc, char **argv);
        };
    }
}

#endif
