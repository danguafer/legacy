#pragma once

#include <Veritas/Definitions/Definitions.h>

namespace Silexars {
    namespace System {
        namespace IO {
            class Node {
                public:
                    virtual uint8 getNodeType() const = 0;

                    enum TYPES { NONE, GLOBAL, NET, FILE, DEVICE };
            };
        }
    }
}
