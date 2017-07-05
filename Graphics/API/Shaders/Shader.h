#pragma once

#include <Veritas/Definitions/Definitions.h>

namespace Silexars {
    namespace Graphics {
        namespace API {
            class RenderProgram;
            class ComputeProgram;
            namespace Shaders {
                class Shader {
                    public:
                        ~Shader();

                        bool isValid() const;
                        const char* getMessage() const;
                        const char* getSource() const;
                    protected:
                        friend class API::RenderProgram;
                        friend class API::ComputeProgram;

                        Shader(const char* source, uint32 type);
                        Handle id;

                        bool isvalid;
                        char *source, *message;

                        uint32 nInLocations;
                        class Location {
                            public:
                                Location(const char *name, int32 index);
                                ~Location();
                                char *name;
                                int32 index;
                        };
                        Location** inLocations;

                        void processLayout(void *s);
                        void processUniformBlock(void *s);
                };
            }
        }
    }
}
