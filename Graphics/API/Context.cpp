#include "Context.h"
#define DEF_DECL
#define GLEXT_IMPL
#include "third-party/glLoader/glLoader.h"
#include <cstring>
#include <Veritas/Definitions/Definitions.h>
#include <Veritas/System/UI/GLContext.h>

using namespace Silexars::Graphics::API;
using namespace Buffers;
using namespace Samplers;
using namespace Shaders;

using namespace Silexars::System::UI;

#ifdef ANDROID
#include <android/log.h>
#endif

Context::Context(void (*fmakeCurrent)(void *data), void (*fswapBuffers)(void *data), void *data) {
    this->fmakeCurrent = fmakeCurrent;
    this->fswapBuffers = fswapBuffers;
    this->data = data;

    isMultisampling = false;

    boundProgram = 0;
    boundFrameBuffer = 0;
    boundIndexBuffer = 0;
    boundVertexBuffer = 0;

    boundSamplerUnit = 0;
    memset(boundSampler, 0, sizeof(boundSampler));
    memset(boundImage, 0, sizeof(boundImage));

    makeCurrent();

    #ifdef DESKTOP
        #warning CHANGE ALL STATICS FOR THREAD_LOCAL
        static bool notInitialized = true;
        if (notInitialized) {
            glewInit();
            notInitialized = false;
        }
    #endif

    #ifdef OPENGLES
        glFramebufferTexture2DMultisampleIMG = (PFNGLFRAMEBUFFERTEXTURE2DMULTISAMPLEIMG) GLContext::getProcAddress("glFramebufferTexture2DMultisampleIMG");
    #endif

    glDepthFunc(GL_LEQUAL);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // It will probably need to be reimplemented with View::getDimension
    GLint viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);


    pixelReadFrameBuffer = new FrameBuffer();

    defaultFrameBuffer = new FrameBuffer(viewport[2], viewport[3]);
    defaultFrameBuffer->use();

    quad = 0;
    cube = 0;
    sphere = 0;

    #define GLSL(...) #__VA_ARGS__
    VertexShader copyVS(GLSL(
        layout (location = 0) in vec3 vertices;
        layout (location = 2) in vec2 texcoords;

        uniform vec2 position;
        uniform vec2 dimension;

        varying vec2 uv;
        void main(void) {
            gl_Position = vec4(vertices.xy * dimension + position, 0.0, 1.0);
            uv = texcoords;
        }
    ));
    FragmentShader copyFS(GLSL(
        uniform sampler2D source;
        varying vec2 uv;
        void main(void) {
            gl_FragColor = texture2D(source, uv);
        }
    ));
    copyProgram = new RenderProgram(&copyVS, &copyFS);
    copyProgram->setFaceCulling(false);
    copyProgram->setDepthTesting(false);
    clearProgram = new ClearProgram();
    #undef GLSL
}

Context::~Context() {
    delete copyProgram;
    delete clearProgram;

    delete defaultFrameBuffer;
    delete pixelReadFrameBuffer;

    if (quad) {
        delete quad->getIndexBuffer();
        delete quad->getVertexBuffer(0);
        delete quad->getVertexBuffer(1);
        delete quad->getVertexBuffer(2);
        delete quad;
    }
    if (cube) {
        delete cube->getIndexBuffer();
        delete cube->getVertexBuffer(0);
        delete cube->getVertexBuffer(1);
        delete cube->getVertexBuffer(2);
        delete cube;
    }
    if (sphere) {
        delete sphere->getIndexBuffer();
        delete sphere->getVertexBuffer(0);
        delete sphere->getVertexBuffer(1);
        delete sphere->getVertexBuffer(2);
        delete sphere;
    }

    if (current == this) current = 0;
}

Context* Context::current = 0;

void Context::makeCurrent() {
    // Don't test against current, because the OpenGL context can be changed outside our API.
    current = this;
    fmakeCurrent(data);
}
Context* Context::getCurrent() { return current; }

void Context::swapBuffers(FrameBuffer *fb, int32 x, int32 y) {
    getDefaultFrameBuffer()->draw(fb, x, y);
    fswapBuffers(data);
}
void Context::swapBuffers(FrameBuffer *fb, int32 x, int32 y, uint32 w, uint32 h) {
    getDefaultFrameBuffer()->draw(fb, x, y, w, h);
    fswapBuffers(data);
}

ClearProgram* Context::getClearProgram() const { return clearProgram; }

FrameBuffer* Context::getDefaultFrameBuffer() const { return defaultFrameBuffer; }

RenderProgram::VertexArrayObject* Context::getQuad() {
    if (!quad) {
        float32 vertices[] = { -1.0f, -1.0f, 0.0f, -1.0f,  1.0f, 0.0f, 1.0f, -1.0f, 0.0f, 1.0f,  1.0f, 0.0f };
        float32 normals[] = { 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f };
        float32 texcoords[] = { 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f };
        uint8 indices[] = { 0, 3, 1, 0, 2, 3 };

        quad = new RenderProgram::VertexArrayObject();
        quad->setVertexBuffer(0, new VertexBuffer(3, 4, VertexBuffer::FLOAT32, vertices));
        quad->setVertexBuffer(1, new VertexBuffer(3, 4, VertexBuffer::FLOAT32, normals));
        quad->setVertexBuffer(2, new VertexBuffer(2, 4, VertexBuffer::FLOAT32, texcoords));
        quad->setIndexBuffer(new IndexBuffer(6, IndexBuffer::UINT8, indices));
    }
    return quad;
}

RenderProgram::VertexArrayObject* Context::getCube() {
    if (!cube) {
        float32 vertices[] = { -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f, -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, 1.0f,1.0f, -1.0f, -1.0f,1.0f, -1.0f, 1.0f,1.0f, 1.0f, -1.0f,1.0f, 1.0f, 1.0f,-1.0f, -1.0f, -1.0f,-1.0f, -1.0f, 1.0f,1.0f, -1.0f, -1.0f,1.0f, -1.0f, 1.0f,-1.0f, 1.0f, -1.0f,-1.0f, 1.0f, 1.0f,1.0f, 1.0f, -1.0f,1.0f, 1.0f, 1.0f,-1.0f, -1.0f, 1.0f,-1.0f, 1.0f, 1.0f,1.0f, -1.0f, 1.0f,1.0f, 1.0f, 1.0f,-1.0f, -1.0f, -1.0f,-1.0f, 1.0f, -1.0f,1.0f, -1.0f, -1.0f,1.0f, 1.0f, -1.0f};
        float32 normals[] = { -1.0f, 0.0f, 0.0f,-1.0f, 0.0f, 0.0f,-1.0f, 0.0f, 0.0f,-1.0f, 0.0f, 0.0f,1.0f, 0.0f, 0.0f,1.0f, 0.0f, 0.0f,1.0f, 0.0f, 0.0f,1.0f, 0.0f, 0.0f,0.0f, -1.0f, 0.0f,0.0f, -1.0f, 0.0f,0.0f, -1.0f, 0.0f,0.0f, -1.0f, 0.0f,0.0f,  1.0f, 0.0f,0.0f,  1.0f, 0.0f,0.0f,  1.0f, 0.0f,0.0f,  1.0f, 0.0f,0.0f,  0.0f,  1.0f,0.0f,  0.0f,  1.0f,0.0f,  0.0f,  1.0f,0.0f,  0.0f,  1.0f,0.0f,  0.0f, -1.0f,0.0f,  0.0f, -1.0f,0.0f,  0.0f, -1.0f,0.0f,  0.0f, -1.0f};
        float32 texcoords[] = { 0.0f, 0.0f,0.0f, 1.0f,1.0f, 0.0f,1.0f, 1.0f,0.0f, 0.0f,0.0f, 1.0f,1.0f, 0.0f,1.0f, 1.0f,0.0f, 0.0f,0.0f, 1.0f,1.0f, 0.0f,1.0f, 1.0f,0.0f, 0.0f,0.0f, 1.0f,1.0f, 0.0f,1.0f, 1.0f,0.0f, 0.0f,0.0f, 1.0f,1.0f, 0.0f,1.0f, 1.0f,0.0f, 0.0f,0.0f, 1.0f,1.0f, 0.0f,1.0f, 1.0f};
        uint8 indices[] = { 0, 1, 3, 0, 3, 2,4, 7, 5, 4, 6, 7,8, 11, 9, 8, 10, 11,12, 13, 15, 12, 15, 14,16, 19, 17, 16, 18, 19,20, 21, 23, 20, 23, 22};

        cube = new RenderProgram::VertexArrayObject;
        cube->setVertexBuffer(0, new VertexBuffer(3, sizeof(vertices)/sizeof(float32)/3, VertexBuffer::FLOAT32, vertices));
        cube->setVertexBuffer(1, new VertexBuffer(3, sizeof(normals)/sizeof(float32)/3, VertexBuffer::FLOAT32, normals));
        cube->setVertexBuffer(2, new VertexBuffer(2, sizeof(texcoords)/sizeof(float32)/2, VertexBuffer::FLOAT32, texcoords));
        cube->setIndexBuffer(new IndexBuffer(sizeof(indices), IndexBuffer::UINT8, indices));
    }
    return cube;
}

#include <Veritas/Math/Math.h>

RenderProgram::VertexArrayObject* Context::getSphere() {
    if (!sphere) {
        #define D 16
        float32 vertices[D*D*3];
        float32 normals[D*D*3];
        float32 texcoords[D*D*2];
        uint8 indices[(D-1)*(D-1)*2*3] = { 0, 2, 3, 0, 3, 1 };
        for (uint32 i = 0; i < D; i++) {
            float32 v = i/(float32) (D-1);
            float32 y = (v - 0.5f)*2.0f;
            float32 h = sqrt(1.0f - y*y);

            for (uint32 j = 0; j < D; j++) {
                float32 u = j/(float32) (D-1);
                float32 a = u * (PI * 2.0f);
                float32 x = cos(a) * h;
                float32 z = sin(a) * h;

                uint32 vidx = (i*D) + j;
                uint32 vidx3c = vidx * 3;
                uint32 vidx2c = vidx * 2;

                normals[vidx3c + 0] = vertices[vidx3c + 0] = x;
                normals[vidx3c + 1] = vertices[vidx3c + 1] = y;
                normals[vidx3c + 2] = vertices[vidx3c + 2] = z;

                texcoords[vidx2c] = 1.0 - u;
                texcoords[vidx2c + 1] = v;
            }
        }
        for (uint32 i = 0; i < D - 1; i++)
            for (uint32 j = 0; j < D - 1; j++) {
                #define VIDX(X, Y) (((Y)*D + (X)))
                uint32 iidx = (i*(D - 1) + j) * 6;
                uint32 i0 = VIDX(j + 0, i + 0);
                uint32 i1 = VIDX(j + 1, i + 0);
                uint32 i2 = VIDX(j + 0, i + 1);
                uint32 i3 = VIDX(j + 1, i + 1);
                indices[iidx + 0] = i0;
                indices[iidx + 1] = i2;
                indices[iidx + 2] = i3;
                indices[iidx + 3] = i0;
                indices[iidx + 4] = i3;
                indices[iidx + 5] = i1;
                #undef IDX
            }

        #undef W
        #undef H

        sphere = new RenderProgram::VertexArrayObject;
        sphere->setVertexBuffer(0, new VertexBuffer(3, sizeof(vertices)/sizeof(float32)/3, VertexBuffer::FLOAT32, vertices));
        sphere->setVertexBuffer(1, new VertexBuffer(3, sizeof(normals)/sizeof(float32)/3, VertexBuffer::FLOAT32, normals));
        sphere->setVertexBuffer(2, new VertexBuffer(2, sizeof(texcoords)/sizeof(float32)/2, VertexBuffer::FLOAT32, texcoords));
        sphere->setIndexBuffer(new IndexBuffer(sizeof(indices), IndexBuffer::UINT8, indices));
    }
    return sphere;
}
