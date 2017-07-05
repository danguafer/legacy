#ifndef SILEXARS_SYSTEM_THREAD_H
#define SILEXARS_SYSTEM_THREAD_H

#include <Veritas/Definitions/Definitions.h>

namespace Silexars {
    namespace System {
        class Thread {
            public:
                Thread(void* (*f)(void *data), void *data = 0);

                void* join();

                static void sleep(uint64 ms);
            private:
                Handle id;
        };
    }
}

#endif // THREAD_H
