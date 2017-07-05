//!Complete

#ifndef SILEXARS_SYSTEM_MANAGERS_WINDOWMANAGER_H_
#define SILEXARS_SYSTEM_MANAGERS_WINDOWMANAGER_H_

#include <Veritas/Definitions/Definitions.h>
#include "../UI/Window.h"
#include <list>

namespace Silexars {
    namespace System {
        namespace Managers {
            class Manager;
            class WindowManager {
                private:
                    typedef std::list<UI::Window*> List;
                public:
                    typedef List::iterator iterator;

                    iterator begin();
                    iterator end();
                    uint32 size() const;
                private:
                    friend class Manager;
                    friend class UI::Window;
                    List windows;

                    WindowManager();
                    ~WindowManager();

                    void manage();
            };
        }
    }
}

#endif
