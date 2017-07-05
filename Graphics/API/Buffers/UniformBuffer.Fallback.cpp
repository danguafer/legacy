#include "UniformBuffer.Fallback.h"

#include "../Program.h"
#include <Veritas/Data/String.h>
#include <cstring>
#include <iostream>
#include <cstdlib>

using namespace Silexars;
using namespace Data;
using namespace Graphics::API;
using namespace Buffers;

UniformBuffer::Fallback::Fallback(const char *source) {
    uniforms = 0;
    nuniforms = 0;

    nprograms = 0;
    programs = 0;
    locations = 0;

    this->source = new char[strlen(source)];
    strcpy(this->source, source);

    String blockCode(source);
    uint32 statement = -1;
    uint32 offset = 0;
    do {
        uint32 len;
        statement++;
        statement = blockCode.nextWord(statement, &len);
        if (statement == String::npos) break;

        String typeName = blockCode.substr(statement, len);
        uint32 varSize = 4;
        uint8 varType;
        if (typeName.indexOf("vec") != String::npos) varSize *= typeName.toInt32(typeName.length() - 1);
        else if (typeName.indexOf("mat") != String::npos) {
            uint32 n = typeName.toInt32(typeName.length() - 1);
            varSize *= n * n;
        }
        if (typeName.indexOf("uvec") != String::npos || typeName.indexOf("uint") != String::npos) varType = Uniform::UINT;
        else if (typeName.indexOf("ivec") != String::npos || typeName.indexOf("int") != String::npos || typeName.indexOf("bool") != String::npos) varType = Uniform::INT;
        else if (typeName.indexOf("mat") != String::npos) varType = Uniform::MATRIX;
        else varType = Uniform::FLOAT;

        statement = blockCode.nextWord(statement + len, &len);
        uint32 comma = blockCode.indexOf(statement, ';') - statement; if (comma < len) len = comma;

        String fieldName = blockCode.substr(statement, len);

        nuniforms++;
        uniforms = (Uniform**) realloc(uniforms, sizeof(Uniform*) * nuniforms);
        uniforms[nuniforms - 1] = new Uniform(fieldName.c_str(), offset, varSize, varType);

        offset += varSize;
    } while ((statement = blockCode.indexOf(statement, ';')) != String::npos);

    buffer = malloc(offset);
}

UniformBuffer::Fallback::~Fallback() {
    for (uint32 i = 0; i < nuniforms; i++) delete uniforms[i];
    delete[] source;
    free(uniforms);
    free(buffer);

    for (uint32 i = 0; i < nprograms; i++) free(locations[i]);
    free(locations);
    free(programs);
}

bool UniformBuffer::Fallback::isValid() const { return true; }
const char* UniformBuffer::Fallback::getMessage() const { return ""; }
const char* UniformBuffer::Fallback::getSource() const { return source; }

int32 UniformBuffer::Fallback::getUniformLocation(const char *uniform) const {
    for (uint32 i = 0; i < nuniforms; i++)
        if (!strcmp(uniform, uniforms[i]->name))
            return i;
    return -1;
}

void UniformBuffer::Fallback::uniform(int32 location, float32 *value) { uniform(location, *value); }
void UniformBuffer::Fallback::uniform(int32 location, int32 *value) { uniform(location, *value); }
void UniformBuffer::Fallback::uniform(int32 location, uint32 *value) { uniform(location, *value); }

void UniformBuffer::Fallback::uniform(int32 location, float32 value) {
    *((float32*) ((uint8*) buffer) + uniforms[location]->offset) = value;
    for (uint32 i = 0; i < nprograms; i++) programs[i]->getLocalUniformBuffer()->uniform(locations[i][location], value);
}
void UniformBuffer::Fallback::uniform(int32 location, int32 value) {
    *((int32*) ((uint8*) buffer) + uniforms[location]->offset) = value;
    for (uint32 i = 0; i < nprograms; i++) programs[i]->getLocalUniformBuffer()->uniform(locations[i][location], value);
}
void UniformBuffer::Fallback::uniform(int32 location, uint32 value) {
    *((uint32*) ((uint8*) buffer) + uniforms[location]->offset) = value;
    for (uint32 i = 0; i < nprograms; i++) programs[i]->getLocalUniformBuffer()->uniform(locations[i][location], value);
}
void UniformBuffer::Fallback::uniform2(int32 location, float32* value) {
    memcpy(&((uint8*) buffer)[uniforms[location]->offset], value, 4 * 2);
    for (uint32 i = 0; i < nprograms; i++) programs[i]->getLocalUniformBuffer()->uniform2(locations[i][location], value);
}
void UniformBuffer::Fallback::uniform2(int32 location, int32* value) {
    memcpy(&((uint8*) buffer)[uniforms[location]->offset], value, 4 * 2);
    for (uint32 i = 0; i < nprograms; i++) programs[i]->getLocalUniformBuffer()->uniform2(locations[i][location], value);
}
void UniformBuffer::Fallback::uniform2(int32 location, uint32* value) {
    memcpy(&((uint8*) buffer)[uniforms[location]->offset], value, 4 * 2);
    for (uint32 i = 0; i < nprograms; i++) programs[i]->getLocalUniformBuffer()->uniform2(locations[i][location], value);
}
void UniformBuffer::Fallback::uniform3(int32 location, float32* value) {
    memcpy(&((uint8*) buffer)[uniforms[location]->offset], value, 4 * 3);
    for (uint32 i = 0; i < nprograms; i++) programs[i]->getLocalUniformBuffer()->uniform3(locations[i][location], value);
}
void UniformBuffer::Fallback::uniform3(int32 location, int32* value) {
    memcpy(&((uint8*) buffer)[uniforms[location]->offset], value, 4 * 3);
    for (uint32 i = 0; i < nprograms; i++) programs[i]->getLocalUniformBuffer()->uniform3(locations[i][location], value);
}
void UniformBuffer::Fallback::uniform3(int32 location, uint32* value) {
    memcpy(&((uint8*) buffer)[uniforms[location]->offset], value, 4 * 3);
    for (uint32 i = 0; i < nprograms; i++) programs[i]->getLocalUniformBuffer()->uniform3(locations[i][location], value);
}
void UniformBuffer::Fallback::uniform4(int32 location, float32* value) {
    memcpy(&((uint8*) buffer)[uniforms[location]->offset], value, 4 * 4);
    for (uint32 i = 0; i < nprograms; i++) programs[i]->getLocalUniformBuffer()->uniform4(locations[i][location], value);
}
void UniformBuffer::Fallback::uniform4(int32 location, int32* value) {
    memcpy(&((uint8*) buffer)[uniforms[location]->offset], value, 4 * 4);
    for (uint32 i = 0; i < nprograms; i++) programs[i]->getLocalUniformBuffer()->uniform4(locations[i][location], value);
}
void UniformBuffer::Fallback::uniform4(int32 location, uint32* value) {
    memcpy(&((uint8*) buffer)[uniforms[location]->offset], value, 4 * 4);
    for (uint32 i = 0; i < nprograms; i++) programs[i]->getLocalUniformBuffer()->uniform4(locations[i][location], value);
}
void UniformBuffer::Fallback::uniform2x2(int32 location, float32 *value) {
    memcpy(&((uint8*) buffer)[uniforms[location]->offset], value, 4 * 2 * 2);
    for (uint32 i = 0; i < nprograms; i++) programs[i]->getLocalUniformBuffer()->uniform2x2(locations[i][location], value);
}
void UniformBuffer::Fallback::uniform3x3(int32 location, float32 *value) {
    memcpy(&((uint8*) buffer)[uniforms[location]->offset], value, 4 * 3 * 3);
    for (uint32 i = 0; i < nprograms; i++) programs[i]->getLocalUniformBuffer()->uniform3x3(locations[i][location], value);
}

void UniformBuffer::Fallback::uniform4x4(int32 location, float32 *value) {
    memcpy(&((uint8*) buffer)[uniforms[location]->offset], value, 4 * 4 * 4);
    for (uint32 i = 0; i < nprograms; i++) programs[i]->getLocalUniformBuffer()->uniform4x4(locations[i][location], value);
}

UniformBuffer::Fallback::Uniform::Uniform(const char *name, uint16 offset, uint8 size, uint8 type) {
    this->name = new char[strlen(name) + 1]; strcpy(this->name, name);
    this->offset = offset;
    this->size = size;
    this->type = type;
}
UniformBuffer::Fallback::Uniform::~Uniform() { delete[] name; }


#include <cmath>

void uniform1u(IUniformBuffer *ubo, int32 location, void *value) { ubo->uniform(location, (uint32*) value); }
void uniform1i(IUniformBuffer *ubo, int32 location, void *value) { ubo->uniform(location, (int32*) value); }
void uniform1f(IUniformBuffer *ubo, int32 location, void *value) { ubo->uniform(location, (float32*) value); }

void uniform2u(IUniformBuffer *ubo, int32 location, void *value) { ubo->uniform2(location, (uint32*) value); }
void uniform2i(IUniformBuffer *ubo, int32 location, void *value) { ubo->uniform2(location, (int32*) value); }
void uniform2f(IUniformBuffer *ubo, int32 location, void *value) { ubo->uniform2(location, (float32*) value); }

void uniform3u(IUniformBuffer *ubo, int32 location, void *value) { ubo->uniform3(location, (uint32*) value); }
void uniform3i(IUniformBuffer *ubo, int32 location, void *value) { ubo->uniform3(location, (int32*) value); }
void uniform3f(IUniformBuffer *ubo, int32 location, void *value) { ubo->uniform3(location, (float32*) value); }

void uniform4u(IUniformBuffer *ubo, int32 location, void *value) { ubo->uniform3(location, (uint32*) value); }
void uniform4i(IUniformBuffer *ubo, int32 location, void *value) { ubo->uniform3(location, (int32*) value); }
void uniform4f(IUniformBuffer *ubo, int32 location, void *value) { ubo->uniform3(location, (float32*) value); }

void uniform22(IUniformBuffer *ubo, int32 location, void *value) { ubo->uniform2x2(location, (float32*) value); }
void uniform33(IUniformBuffer *ubo, int32 location, void *value) { ubo->uniform3x3(location, (float32*) value); }
void uniform44(IUniformBuffer *ubo, int32 location, void *value) { ubo->uniform4x4(location, (float32*) value); }

void (*funiform[])(IUniformBuffer *ubo, int32 location, void *value) = { uniform1u, uniform1i, uniform1f, uniform2u, uniform2i, uniform2f, uniform3u, uniform3i, uniform3f, uniform4u, uniform4i, uniform4f, uniform22, uniform33, uniform44 };

void UniformBuffer::Fallback::bindTo(Program *program) {
    nprograms++;
    programs = (Program**) realloc(programs, sizeof(Program*) * nprograms);
    locations = (int32**) realloc(locations, sizeof(int32*) * nprograms);
    programs[nprograms - 1] = program;
    locations[nprograms - 1] = (int32*) malloc(sizeof(int32) * nuniforms);

    UniformBuffer *local = program->getLocalUniformBuffer();

    for (uint32 i = 0; i < nuniforms; i++) {
        Uniform *uniform = uniforms[i];
        int32 location = local->getUniformLocation(uniform->name);
        locations[nprograms - 1][i] = location;
        funiform[(int32) (uniform->type == Uniform::MATRIX ? round(uniform->size/20.0f) + 11.0f : (uniform->size/4 - 1) * 3 + uniform->type)](local, location, ((uint8*) buffer) + uniform->offset);
    }
}
void UniformBuffer::Fallback::unbindFrom(Program *program) {
    for (uint32 i = 0; i < nprograms; i++) if (programs[i] == program) {
        Program *tmp = programs[i];
        programs[i] = programs[nprograms - 1];
        nprograms--;
    }
}
