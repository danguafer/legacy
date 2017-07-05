#pragma once

#include <Veritas/Definitions/Definitions.h>

#include <Veritas/Graphics/API/API.h>
#include <Veritas/Math/Math.h>
#include <stack>

namespace Silexars {
    namespace Graphics {
        namespace Canvas {
            class Canvas3D {
                public:
                    Canvas3D(API::Context *ctx, API::Buffers::FrameBuffer *framebuffer);
                    ~Canvas3D();

                    void setFrameBuffer(API::Buffers::FrameBuffer *fb);
                    API::Buffers::FrameBuffer* getFrameBuffer() const;
                    API::Shaders::VertexShader* getVertexShader() const;

                    void save();
                    void restore();

                    void translate(const Math::vec3& translation);
                    void scale(const Math::vec3& scaling);
                    void rotateX(float32 a);
                    void rotateY(float32 a);
                    void rotateZ(float32 a);

                    void setTransformation(const Math::mat4& transformation);
                    const Math::mat4& getTransformation();

                    void setFillColor(const Math::vec4& color);
                    const Math::vec4& getFillColor() const;

                    void setStrokeColor(const Math::vec4& color);
                    const Math::vec4& getStrokeColor() const;

                    void clear();

                    void fillBox(const Math::vec3& position, const Math::vec3& dimension);
                    void fillBox(API::RenderProgram *renderProgram, const Math::vec3 &position, const Math::vec3 &dimension);

                    void strokeBox(const Math::vec3& position, const Math::vec3& dimension);

                    void strokeLine(const Math::vec3& p0, const Math::vec3& p1);
                private:
                    struct State {
                        Math::mat4 projection, transformation;
                        Math::vec4 fillColor, strokeColor;
                    };
                    typedef std::stack<State*> StateStack;
                    StateStack stateStack;

                    API::Shaders::VertexShader *vs;

                    API::Context *ctx;
                    API::Buffers::FrameBuffer *fb;

                    API::RenderProgram::VertexArrayObject *boxTriangles, *boxLines;
                    API::RenderProgram::VertexArrayObject *line;

                    API::RenderProgram *colorProgram;
            };
        }
    }
}
