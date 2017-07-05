#include "Program.h"
#include "Context.h"
#include "third-party/glLoader/glLoader.h"
#include <cstring>
#include <cstdlib>

using namespace Silexars::Graphics::API;
using namespace Buffers;

Program::Program() {
    id = (Handle) glCreateProgram();
    localubo = new UniformBuffer(this);
}
Program::~Program() {
    glDeleteProgram((GLuint) id);
    delete[] message;
    delete localubo;

    for (uint32 i = 0; i < ubos.nbindings; i++) ((UniformBuffer*) ubos.bindings[i].object)->unbindFrom(this);
}

bool Program::isValid() const { return isvalid; }
const char* Program::getMessage() const { return message; }

int32 Program::getUniformBufferLocation(const char *uniformBuffer) const { return -1; }

void Program::uniformBuffer(const char *name, UniformBuffer *ubo) { uniformBuffer(getUniformBufferLocation(name), ubo); }
void Program::uniformBuffer(int32 location, Buffers::UniformBuffer *ubo) {
    for (uint32 i = 0; i < ubos.nbindings; i++) {
        if (ubos.bindings[i].location == location) {
            ubos.set(location, ubo);
            ((Buffers::UniformBuffer*) ubos.bindings[i].object)->unbindFrom(this);
            ubo->bindTo(this);
            return;
        }
    }

    ubos.set(location, ubo);
    ubo->bindTo(this);
}

void Program::link() {
    glLinkProgram((GLuint) id);

    GLint ret; glGetProgramiv((GLuint) id, GL_LINK_STATUS, &ret);
    isvalid = ret;

    if (!isValid()) {
        glGetProgramiv((GLuint) id, GL_INFO_LOG_LENGTH, &ret);
        message = new char[ret];
        GLint l; glGetProgramInfoLog((GLuint) id, ret, &l, message);
    } else message = 0;
}

void Program::use() {
    if (Context::current->boundProgram != this) {
        Context::current->boundProgram  = this;
        glUseProgram((GLuint) id);
    }
}

UniformBuffer* Program::getLocalUniformBuffer() const { return localubo; }


#include <cstdlib>

Program::LocationBinding::LocationBinding(int32 location, void *object, uint32 permission) {
    this->location = location;
    this->object = object;
    this->permission = permission;
}

Program::LocationBindings::LocationBindings() {
    nbindings = 0;
    bindings = 0;
}

Program::LocationBindings::~LocationBindings() {
    free(bindings);
}

uint32 Program::LocationBindings::set(int32 location, void *object, uint32 permission) {
    for (uint32 i = 0; i < nbindings; i++)
        if (bindings[i].location == location) {
            bindings[i].object = object;
            bindings[i].permission = permission;
            return i;
        }

    nbindings++;
    bindings = (LocationBinding*) realloc(bindings, nbindings*sizeof(LocationBinding));
    bindings[nbindings - 1] = LocationBinding(location, object, permission);
    return nbindings - 1;
}
