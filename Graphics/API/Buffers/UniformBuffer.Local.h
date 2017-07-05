#ifndef SILEXARS_GRAPHICS_API_BUFFERS_UNIFORMBUFFER_LOCAL_H
#define SILEXARS_GRAPHICS_API_BUFFERS_UNIFORMBUFFER_LOCAL_H

#include "UniformBuffer.h"

namespace Silexars {
    namespace Graphics {
        namespace API {
            namespace Buffers {
                class UniformBuffer::Local : public IUniformBuffer {
                    public:
                        Local(Program *program);

                        bool isValid() const;
                        const char* getMessage() const;
                        const char* getSource() const;

                        int32 getUniformLocation(const char *name) const;

                        void uniform(int32 location, uint32 value);
                        void uniform(int32 location, int32 value);
                        void uniform(int32 location, float32 value);

                        void uniform(int32 location, uint32* value);
                        void uniform(int32 location, int32* value);
                        void uniform(int32 location, float32* value);

                        void uniform2(int32 location, uint32* value);
                        void uniform2(int32 location, int32* value);
                        void uniform2(int32 location, float32* value);

                        void uniform3(int32 location, uint32* value);
                        void uniform3(int32 location, int32* value);
                        void uniform3(int32 location, float32* value);

                        void uniform4(int32 location, uint32* value);
                        void uniform4(int32 location, int32* value);
                        void uniform4(int32 location, float32* value);

                        void uniform2x2(int32 location, float32* value);
                        void uniform3x3(int32 location, float32* value);
                        void uniform4x4(int32 location, float32* value);
                    private:
                        void bindTo(Program *program);
                        void unbindFrom(Program *program);

                        Program *program;
                };
            }
        }
    }
}

#endif // UNIFORMBUFFER_LOCAL_H
