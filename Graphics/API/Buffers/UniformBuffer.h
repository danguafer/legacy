#pragma once

#include "Buffer.h"
#include "IUniformBuffer.h"
#include <list>

namespace Silexars {
    namespace Graphics {
        namespace API {
            class Program;
            namespace Buffers {
                class UniformBuffer : public Buffer, public IUniformBuffer {
                    public:
                        UniformBuffer(const char *source);
                        ~UniformBuffer();

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

                        template <class T> void uniform(const char *name, T value) { uniform(getUniformLocation(name), value); }
                        template <class T> void uniform2(const char *name, T value) { uniform2(getUniformLocation(name), value); }
                        template <class T> void uniform3(const char *name, T value) { uniform3(getUniformLocation(name), value); }
                        template <class T> void uniform4(const char *name, T value) { uniform4(getUniformLocation(name), value); }
                        template <class T> void uniform2x2(const char *name, T value) { uniform2x2(getUniformLocation(name), value); }
                        template <class T> void uniform3x3(const char *name, T value) { uniform3x3(getUniformLocation(name), value); }
                        template <class T> void uniform4x4(const char *name, T value) { uniform4x4(getUniformLocation(name), value); }
                    private:
                        friend class API::Program;

                        UniformBuffer(Program *program);
                        IUniformBuffer *ubimpl;

                        class Local;
                        class Fallback;
                        class Core;

                        void bindTo(API::Program *program);
                        void unbindFrom(API::Program *program);
                };
            }
        }
    }
}
