#ifndef SILEXARS_GRAPHICS_API_BUFFERS_UNIFORMBUFFER_FALLBACK_H
#define SILEXARS_GRAPHICS_API_BUFFERS_UNIFORMBUFFER_FALLBACK_H

#include "UniformBuffer.h"

namespace Silexars {
    namespace Graphics {
        namespace API {
            namespace Buffers {
                class UniformBuffer::Fallback : public IUniformBuffer {
                    public:
                        Fallback(const char *source);
                        ~Fallback();

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
                        uint32 nprograms;
                        Program **programs;
                        int32 **locations;

                        void *buffer;

                        char *source;

                        class Uniform {
                            public:
                                Uniform(const char *name, uint16 offset, uint8 size, uint8 type);
                                ~Uniform();
                                char *name;
                                uint16 offset;
                                uint8 size;
                                uint8 type;
                                enum TYPES { UINT, INT, FLOAT, MATRIX };
                        };

                        uint32 nuniforms;
                        Uniform **uniforms;

                        void bindTo(Program *program);
                        void unbindFrom(Program *program);
                };
            }
        }
    }
}

#endif // UNIFORMBUFFER_FALLBACK_H
