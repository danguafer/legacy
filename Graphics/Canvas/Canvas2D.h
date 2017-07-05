#pragma once

#include <Veritas/Definitions/Definitions.h>

#include <Veritas/Graphics/API/API.h>
#include <Veritas/Graphics/Font/Font.h>
#include <Veritas/Math/Math.h>
#include <stack>

namespace Silexars {
    namespace Graphics {
        namespace Canvas {
            class Canvas2D {
                public:
                    Canvas2D(API::Context *ctx, API::Buffers::FrameBuffer *framebuffer);
                    ~Canvas2D();

                    uint32 getWidth() const;
                    uint32 getHeight() const;

                    Math::vec2 getDimension() const;

                    void save();
                    void restore();

                    void translate(const Math::vec2& translation);
                    void scale(const Math::vec2& scaling);
                    void rotate(float32 a);

                    void setTransformation(const Math::mat3& transformation);
                    const Math::mat3& getTransformation();

                    void setFillColor(const Math::vec4& fillColor);
                    const Math::vec4& getFillColor() const;

                    void setStrokeColor(const Math::vec4& strokeColor);
                    const Math::vec4& getStrokeColor() const;

                    void clearRect(const Math::vec2& position, const Math::vec2& dimension);
                    void clipRect (const Math::vec2& position, const Math::vec2& dimension);

                    void fillRect(const Math::vec2& position, const Math::vec2& dimension);
                    void fillRect(API::RenderProgram *renderProgram, const Math::vec2& position, const Math::vec2& dimension);
                    void fillRect(API::RenderProgram *renderProgram, const Math::vec2& sresolution, const Math::vec2& sposition, const Math::vec2& sdimension, const Math::vec2 &position, const Math::vec2 &dimension);

                    void fillCircle(const Math::vec2& position, float32 radius);

                    void strokeRect(const Math::vec2& position, const Math::vec2& dimension);
                    void strokeCircle(const Math::vec2& position, const float32 radius);

                    void drawImage(API::Samplers::Sampler2D *image, const Math::vec2&  position);
                    void drawImage(API::Samplers::Sampler2D *image, const Math::vec2&  position, const Math::vec2&  dimension);
                    void drawImage(API::Samplers::Sampler2D *image, const Math::vec2& sposition, const Math::vec2& sdimension, const Math::vec2& dposition, const Math::vec2& ddimension);

                    void setOpacity(float32 opacity);
                    float32 getOpacity() const;

                    void setFontSize(float32 size);
                    float32 getFontSize() const;

                    void setFont(Font* font);
                    Font* getFont() const;

                    void fillText(API::Samplers::Sampler2D *image, const char* text, const Math::vec2& position);
                    void fillText(const char* text, const Math::vec2& position);

                    Math::vec2 measureText(const char *text, Math::vec2* offset = 0) const;

                    void setFrameBuffer(API::Buffers::FrameBuffer *fb);
                    API::Buffers::FrameBuffer* getFrameBuffer() const;
                    API::Shaders::VertexShader* getVertexShader() const;
            private:
                    struct State {
                        Math::mat3 transformation;
                        Math::vec4 fillColor, strokeColor;
                        float32 fontSize;
                        Font* font;
                        Font::Map* fontMap;
                        API::Samplers::Sampler2D* fontImage;
                        float32 opacity;
                    };
                    typedef std::stack<State*> StateStack;
                    StateStack stateStack;

                    API::Samplers::Sampler2D *circle;

                    API::Context *ctx;
                    API::Buffers::FrameBuffer *fb;

                    API::Shaders::VertexShader *vs;

                    API::RenderProgram *rp, *circlerp, *textrp;

                    API::RenderProgram *fillRectRP;
                    API::RenderProgram *fillCircleRP;
                    API::RenderProgram *fillTextRP;
                    API::RenderProgram *drawImageRP;
                    API::RenderProgram *clearRectRP;
            };
        }
    }
}
