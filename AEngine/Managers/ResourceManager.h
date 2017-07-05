#pragma once

#include <Veritas/Definitions/Definitions.h>

namespace Silexars {
    namespace AEngine {
        namespace Managers {
            class ResourceManager {
                public:
                    // Move it to ResourceManager.Resource.h
                    class Resource {
                    public:
                        uint8 getType() const;

                        enum TYPE { IMAGE };
                    };

                    Resource* getResource(const char* path);
                private:
            };
        }
    }
}
