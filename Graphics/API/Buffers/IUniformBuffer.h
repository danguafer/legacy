#pragma once

#include <Veritas/Definitions/Definitions.h>

namespace Silexars {
    namespace Graphics {
        namespace API {
            class Program;
            namespace Buffers {
                class UniformBuffer;
                class IUniformBuffer {
                    public:
                        virtual ~IUniformBuffer();

                        virtual bool isValid() const = 0;
                        virtual const char* getMessage() const = 0;
                        virtual const char* getSource() const = 0;

                        virtual int32 getUniformLocation(const char *name) const = 0;

                        virtual void uniform(int32 location, uint32 value)  = 0;
                        virtual void uniform(int32 location, int32 value)  = 0;
                        virtual void uniform(int32 location, float32 value)  = 0;

                        virtual void uniform(int32 location, uint32* value)  = 0;
                        virtual void uniform(int32 location, int32* value)  = 0;
                        virtual void uniform(int32 location, float32* value)  = 0;

                        virtual void uniform2(int32 location, uint32* value) = 0;
                        virtual void uniform2(int32 location, int32* value) = 0;
                        virtual void uniform2(int32 location, float32* value) = 0;

                        virtual void uniform3(int32 location, uint32* value) = 0;
                        virtual void uniform3(int32 location, int32* value) = 0;
                        virtual void uniform3(int32 location, float32* value) = 0;

                        virtual void uniform4(int32 location, uint32* value) = 0;
                        virtual void uniform4(int32 location, int32* value) = 0;
                        virtual void uniform4(int32 location, float32* value) = 0;

                        virtual void uniform2x2(int32 location, float32* value) = 0;
                        virtual void uniform3x3(int32 location, float32* value) = 0;
                        virtual void uniform4x4(int32 location, float32* value) = 0;
                    protected:
                        friend class UniformBuffer;
                        virtual void bindTo(API::Program *program) = 0;
                        virtual void unbindFrom(API::Program *program) = 0;
                };
            }
        }
    }
}
