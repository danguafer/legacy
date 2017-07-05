#include "Canvas2D.h"
#include <iostream>

using namespace Silexars;
using namespace Graphics;
using namespace Canvas;

using namespace API;
using namespace Buffers;
using namespace Shaders;
using namespace Samplers;

using namespace Math;

#define GLSL(...) #__VA_ARGS__

Canvas2D::Canvas2D(Context *ctx, FrameBuffer *framebuffer) {
    this->ctx = ctx;

    vs = new VertexShader(GLSL(
        layout(location = 0) in vec4 vertices;

        uniform vec2 resolution;

        uniform vec2 sourcePosition;
        uniform vec2 sourceDimension;

        uniform vec2 position;
        uniform vec2 dimension;
        uniform mat3 transformation;

        varying vec2 uv;

        void main(void) {
            vec2 vertice = vertices.xy * 0.5 + 0.5;
            uv = (vertice * sourceDimension + sourcePosition);
            vertice = (2.0*(transformation * vec3(vertice * dimension + position, 1.0)).xy/resolution - 1.0) * vec2(1.0, -1.0);
            gl_Position = vec4(vertice, 0.0, 1.0);
        }
    ));
    FragmentShader *fs = new FragmentShader(GLSL(
        uniform sampler2D image;
        varying vec2 uv;
        void main(void) { gl_FragColor = texture2D(image, uv); }
    ));


    VertexShader rectVS(GLSL(
        layout(location = 0) in vec3 vertices;
        uniform mat3 transformation;
        void main(void) {
            vec3 vertice = transformation * vec3(vertices.xy, 1.0);
            gl_Position = vec4(vertice, 1.0);
        }

    ));
    FragmentShader clearRectFS(GLSL(
        void main(void) { gl_FragColor = vec4(0.0); }
    ));
    FragmentShader fillRectFS(GLSL(
        uniform vec4 fillColor;
        uniform float opacity;
        void main(void) {
            gl_FragColor = fillColor;
            gl_FragColor.a *= opacity;
        }
    ));
    FragmentShader fillCircleFS(GLSL(
        uniform vec4 fillColor;
        uniform float opacity;
        uniform vec2 position;
        uniform float radius;

        void main(void) {
            gl_FragColor = fillColor;
            //gl_FragColor.a *= opacity * step(distance(gl_FragCoord.xy, position), radius);
            gl_FragColor.a *= opacity * smoothstep(1.0, 0.0, distance(gl_FragCoord.xy, position) - radius);
        }
    ));
    FragmentShader drawImageFS(GLSL(
        uniform sampler2D image;
        uniform float opacity;
        void main(void) {
            gl_FragColor = texture2D(image, uv);
            gl_FragColor.a *= opacity;
        }
    ));

    clearRectRP = new RenderProgram(&rectVS, &clearRectFS);
    clearRectRP->setDepthTesting(false);
    clearRectRP->setColorBlending(false);
    clearRectRP->setFaceCulling(false);

    fillRectRP = new RenderProgram(&rectVS, &fillRectFS);
    fillRectRP->setDepthTesting(false);
    fillRectRP->setColorBlending(true);
    fillRectRP->setFaceCulling(false);

    fillCircleRP = new RenderProgram(&rectVS, &fillCircleFS);
    fillCircleRP->setDepthTesting(false);
    fillCircleRP->setColorBlending(true);
    fillCircleRP->setFaceCulling(false);

    drawImageRP = new RenderProgram(&rectVS, &drawImageFS);
    drawImageRP->setDepthRendering(false);
    drawImageRP->setColorBlending(true);
    drawImageRP->setFaceCulling(false);

    rp = new RenderProgram(vs, fs);
    rp->setDepthTesting(false);
    rp->setColorBlending(true);
    rp->setFaceCulling(false);

    delete fs;

    fs = new FragmentShader(GLSL(
        varying vec2 uv;
        uniform vec2 position;
        uniform vec2 dimension;
        uniform vec2 resolution;
        uniform sampler2D color;
        void main(void) {
            vec2 p = gl_FragCoord.xy;
            p.y = resolution.y - p.y;
            float radius = dimension.x/2.0;
            gl_FragColor = texture2D(color, uv) * vec4(vec3(1.0), smoothstep(radius + 0.25, radius - 1.25, distance(p - vec2(radius), position)));
        }
    ));

    circlerp = new RenderProgram(vs, fs);
    circlerp->setDepthTesting(false);
    circlerp->setColorBlending(true);
    circlerp->setFaceCulling(false);

    delete fs;
    fs = new FragmentShader(GLSL(
        uniform sampler2D character;
        uniform sampler2D color;
        varying vec2 uv;
        void main(void) { gl_FragColor = texture2D(color, uv) * vec4(1.0, 1.0, 1.0, texture2D(character, uv).x); }
    ));

    textrp = new RenderProgram(vs, fs);
    textrp->setDepthTesting(false);
    textrp->setColorBlending(true);
    textrp->setFaceCulling(false);

    delete fs;

    #define W 65
    #define R (W/2)
    uint8 data[W*W];
    data[0] = data[1] = data[2] = 0; data[3] = 255;

    for (int32 i = 0; i < W; i++) {
        float32 y = (i - R);
        for (int32 j = 0; j < W; j++) {
            float32 x = (j - R);
            float32 r = sqrt(x*x + y*y);
            data[j + i * W] = r > (float32) R ? 255 : (uint8) (r/(R/255.0f));
        }
    }
    #undef W

    stateStack.push(new State());
    stateStack.top()->font = 0;
    stateStack.top()->fontMap = 0;
    stateStack.top()->fontImage = 0;
    setTransformation(mat3::identity());
    setOpacity(1.0);
    setFillColor(vec4(0.0, 0.0, 0.0, 1.0));
    setStrokeColor(vec4(0.0, 0.0, 0.0, 1.0));
    setFontSize(10.0);

    Font* font = Font::load("arial.ttf");
    if (font) setFont(font);

    setFrameBuffer(framebuffer);
}

Canvas2D::~Canvas2D() {
    delete vs;
    delete rp;
    delete circlerp;
    delete textrp;

    while (stateStack.size()) {
        State* state = stateStack.top();
        delete state->fontMap;
        delete state->fontImage;
        delete state;
        stateStack.pop();
    }
}

uint32 Canvas2D::getWidth() const { return fb->getWidth(); }
uint32 Canvas2D::getHeight() const { return fb->getHeight(); }
vec2 Canvas2D::getDimension() const { return vec2(getWidth(), getHeight()); }

void Canvas2D::setFrameBuffer(FrameBuffer *fb) { this->fb = fb; }
FrameBuffer* Canvas2D::getFrameBuffer() const { return fb; }
VertexShader* Canvas2D::getVertexShader() const { return vs; }

void Canvas2D::setTransformation(const mat3 &transformation) { stateStack.top()->transformation = transformation; }

void Canvas2D::drawImage(Samplers::Sampler2D *image, const vec2 &position) { drawImage(image, position, vec2(image->getWidth(), image->getHeight())); }
void Canvas2D::drawImage(Samplers::Sampler2D *image, const vec2 &position, const vec2 &dimension) { drawImage(image, vec2(0.0f), vec2(image->getWidth(), image->getHeight()), position, dimension); }
void Canvas2D::drawImage(Samplers::Sampler2D *image, const vec2 &sposition, const vec2 &sdimension, const vec2 &position, const vec2 &dimension) {
    rp->sampler("image", image);
    fillRect(rp, vec2(image->getWidth(), image->getHeight()), sposition, sdimension, position, dimension);
}

void Canvas2D::fillRect(const vec2& position, const vec2& dimension) {
    const State* state = stateStack.top();
    UniformBuffer *ub = fillRectRP->getLocalUniformBuffer();

    const vec2 resolution = fb->getDimension();
    const mat3 transformation =  mat3::scaling(dimension * 0.5) * mat3::translation((dimension - resolution) * 0.5 + position) * stateStack.top()->transformation * mat3::scaling(vec2(2.0, -2.0) / resolution);

    ub->uniform3x3("transformation", (float32*) &transformation);
    ub->uniform4("fillColor", (float32*) &state->fillColor);
    ub->uniform("opacity", state->opacity);
    fillRectRP->render(fb, RenderProgram::TRIANGLES, ctx->getQuad());
}
void Canvas2D::fillRect(RenderProgram *rp, const vec2 &position, const vec2 &dimension) { fillRect(rp, vec2(1.0), vec2(0.0), vec2(1.0), position, dimension); }
void Canvas2D::fillRect(RenderProgram *rp, const vec2& sresolution, const vec2 &psposition, const vec2 &psdimension, const vec2 &position, const vec2 &dimension) {
    vec2 sposition = psposition / sresolution;
    vec2 sdimension = psdimension / sresolution;

    vec2 resolution(fb->getWidth(), fb->getHeight());
    rp->getLocalUniformBuffer()->uniform2("resolution", (float32*) &resolution);

    rp->getLocalUniformBuffer()->uniform2("sourcePosition", (float32*) &sposition);
    rp->getLocalUniformBuffer()->uniform2("sourceDimension", (float32*) &sdimension);

    rp->getLocalUniformBuffer()->uniform3x3("transformation", (float32*) &stateStack.top()->transformation);
    rp->getLocalUniformBuffer()->uniform2("position", (float32*) &position);
    rp->getLocalUniformBuffer()->uniform2("dimension", (float32*) &dimension);

    rp->render(fb, RenderProgram::TRIANGLES, ctx->getQuad());
}

void Canvas2D::fillCircle(const vec2 &position, float32 radius) {
    const State* state = stateStack.top();
    UniformBuffer *ub = fillCircleRP->getLocalUniformBuffer();

    const vec2 dimension(radius);

    const vec2 resolution = fb->getDimension();
    const mat3 transformation =  mat3::scaling(dimension) * mat3::translation(position - resolution * 0.5) * stateStack.top()->transformation * mat3::scaling(vec2(2.0, -2.0) / resolution);

    ub->uniform3x3("transformation", (float32*) &transformation);
    ub->uniform4("fillColor", (float32*) &state->fillColor);
    ub->uniform("opacity", state->opacity);

    vec2 invertedPosition = vec2(position.x, resolution.y - position.y);
    ub->uniform2("position", (float32*) &invertedPosition);
    ub->uniform("radius", radius);
    fillCircleRP->render(fb, RenderProgram::TRIANGLES, ctx->getQuad());
}

void Canvas2D::clearRect(const vec2& position, const vec2& dimension) {
    const vec2 resolution = fb->getDimension();
    const mat3 transformation =  mat3::scaling(dimension * 0.5) * mat3::translation((dimension - resolution) * 0.5 + position) * stateStack.top()->transformation * mat3::scaling(vec2(2.0, -2.0) / resolution);
    clearRectRP->getLocalUniformBuffer()->uniform3x3("transformation", (float32*) &transformation);
    clearRectRP->render(fb, RenderProgram::TRIANGLES, ctx->getQuad());
}

void Canvas2D::setFillColor(const vec4& color) { stateStack.top()->fillColor = color; }
const vec4& Canvas2D::getFillColor() const { return stateStack.top()->fillColor; }

void Canvas2D::setStrokeColor(const vec4& color) { stateStack.top()->strokeColor = color; }
const vec4& Canvas2D::getStrokeColor() const { return stateStack.top()->strokeColor; }

void Canvas2D::setOpacity(float32 opacity) { stateStack.top()->opacity = opacity; }
float32 Canvas2D::getOpacity() const { return stateStack.top()->opacity; }

void Canvas2D::scale(const vec2& scaling) { stateStack.top()->transformation = mat3::scaling(scaling) * stateStack.top()->transformation; }
void Canvas2D::translate(const vec2 &translation) { stateStack.top()->transformation = mat3::translation(translation) * stateStack.top()->transformation; }
void Canvas2D::rotate(float32 a) { stateStack.top()->transformation = mat3::zRotation(-a) * stateStack.top()->transformation; }

void Canvas2D::save() {
    State *state = new State();
    *state = *stateStack.top();
    stateStack.push(state);
}
void Canvas2D::restore() {
    if (stateStack.size() > 1) {
        State *state = stateStack.top();
        stateStack.pop();

        delete state->fontMap;
        delete state->fontImage;
        delete state;
    }
}

void Canvas2D::setFontSize(float32 size) { stateStack.top()->fontSize = size; }
float32 Canvas2D::getFontSize() const { return stateStack.top()->fontSize; }

void Canvas2D::setFont(Font *font) {
    uint32 characters[255];
    for (uint32 i = 1; i < 256; i++) characters[i - 1] = i;

    delete stateStack.top()->fontMap;
    delete stateStack.top()->fontImage;

    stateStack.top()->font = font;
    stateStack.top()->fontMap = new Font::Map(font, characters);
    stateStack.top()->fontImage = new Sampler2D(stateStack.top()->fontMap->getImage()->getWidth(), stateStack.top()->fontMap->getImage()->getHeight(), Sampler2D::LUMINANCE, stateStack.top()->fontMap->getImage()->getData());
}
Font* Canvas2D::getFont() const { return stateStack.top()->font; }

void Canvas2D::fillText(const char *text, const vec2 &position) {
    if (!stateStack.top()->font) return;
    vec2 carriage = position;
    uint32 c;

    float32 scalef = getFontSize()/stateStack.top()->font->getHeight();
    Sampler2D* fontImage = stateStack.top()->fontImage;
    vec4 fillColor = stateStack.top()->fillColor;

    for (uint32 i = 0; (c = text[i]); i++) {
        Font::Map::Offset o = stateStack.top()->fontMap->getOffset(c);
        Font::Glyph* g = stateStack.top()->font->getGlyph(c);
        if (!g) continue;
        vec2 offset = vec2(o.x, o.y);
        vec2 dimension = vec2(g->getWidth(), g->getHeight());
        vec2 bearing = vec2(g->getBearingX(), -g->getBearingY());
        textrp->sampler("character", fontImage);
        textrp->getLocalUniformBuffer()->uniform4("color", (float32*) &fillColor);
        fillRect(textrp, vec2(fontImage->getWidth(), fontImage->getHeight()), offset, dimension, bearing * scalef + carriage, dimension * scalef);

        carriage.x += g->getAdvance() * scalef;
        delete g;
    }
}

vec2 Canvas2D::measureText(const char *text, vec2 *offset) const { return getFont()->measureText(text, getFontSize(), offset); }
