#include "Shader.h"
#include "../third-party/glLoader/glLoader.h"
#include <cstring>
#include <cstdlib>

#include <Veritas/Data/String.h>

#include <iostream>
using namespace Silexars;
using namespace Data;
using namespace Graphics::API;
using namespace Shaders;

Shader::Shader(const char *source, uint32 type) {
    nInLocations = 0;
    inLocations = 0;

    this->source = new char[strlen(source) + 1];
    strcpy(this->source, source);

    static char internals[] =
        #ifdef OPENGLES
            "#ifdef GL_FRAGMENT_PRECISION_HIGH\n"
            "precision highp float;\n"
            "#else\n"
            "precision mediump float;\n"
            "#endif\n"
        #endif
            // sampler1D implementation
            "#define sampler1D sampler2D\n"
            "#define texture1D texture1Dimpl\n"
            "vec4 texture1Dimpl(sampler1D sampler, float x) { return texture2D(sampler, vec2(x, 0.0)); }\n\n";

    id = (Handle) glCreateShader(type);

    String code(source);

    switch (type) {
        case GL_FRAGMENT_SHADER: code = internals + code; break;
        case GL_VERTEX_SHADER: processLayout(&code); break;
    }
    processUniformBlock(&code);

    const char *sourcecode = code.c_str();
    glShaderSource((GLuint) id, 1, (const GLchar**) &sourcecode, 0);
    glCompileShader((GLuint) id);

    GLint ret; glGetShaderiv((GLuint) id, GL_COMPILE_STATUS, &ret);
    isvalid = ret;

    if (!isValid()) {
        glGetShaderiv((GLuint) id, GL_INFO_LOG_LENGTH, &ret);
        message = new char[ret];
        GLint l; glGetShaderInfoLog((GLuint) id, ret, &l, message);
    } else message = 0;
}

Shader::~Shader() {
    glDeleteShader((GLuint) id);
    delete[] source;
    delete[] message;

    for (uint32 i = 0; i < nInLocations; i++) delete inLocations[i];
    free(inLocations);
}

bool Shader::isValid() const { return isvalid; }
const char* Shader::getMessage() const { return message; }
const char* Shader::getSource() const { return source; }

void Shader::processLayout(void *s) {
    String *code = (String*) s;
    uint32 layout;
    while ((layout = code->indexOf("layout")) != String::npos) {
        uint32 open = code->indexOf(layout, '('); if (open == String::npos) break;
        uint32 close = code->indexOf(open, ')'); if (close == String::npos) break;
        uint32 location = code->indexOf(open, "location");

        if (location >= open && location <= close) {
            uint32 point = code->toInt32(code->indexOf(location, '=') + 1);
            uint32 in = code->indexOf(close, "in"); if (in == String::npos) break;

            uint32 len;
            uint32 idx = code->nextWord(code->nextWord(in + 2, &len) + len, &len);
            uint32 len2 = code->indexOf(idx, ';') - idx;
            if (len2 < len) len = len2;

            String name = code->substr(idx, len);
            nInLocations++;
            inLocations = (Location**) realloc(inLocations, sizeof(Location*)*nInLocations);
            inLocations[nInLocations - 1] = new Location(name.c_str(), point);

            code->replace(code->substr(layout, in - layout + 2), "attribute");
        }
    }
}

void Shader::processUniformBlock(void *s) {
    String *code = (String*) s;
    uint32 s0 = 0;
    uint32 uniform;
    while ((uniform = code->indexOf(s0, "uniform")) != String::npos) {
        s0 = uniform + 7;
        uint32 len, len2;
        s0 = code->nextWord(s0, &len);

        uint32 blank = code->indexOf(s0, ' ');
        uint32 bracket = code->indexOf(s0, '{');
        if (blank < bracket && code->substr(code->nextWord(blank + 1), 1) != "{") continue;
        if (bracket - s0 < len) len = bracket - s0;

        String blockName = code->substr(s0, len);

        s0 = code->indexOf(s0, '{') + 1;
        bracket = code->indexOf(s0, '}');
        String blockCode = code->substr(s0, bracket - s0);

        uint32 statement = -1;
        do {
            statement++;
            statement = blockCode.nextWord(statement, &len);
            if (statement == String::npos) break;

            blockCode.insert(statement, "uniform ");
            statement += 8;

            statement = blockCode.nextWord(statement + len, &len);
            uint32 comma = blockCode.indexOf(statement, ';') - statement; if (comma < len) len = comma;

            String fieldName = blockCode.substr(statement, len);
        } while ((statement = blockCode.indexOf(statement, ';')) != String::npos);
        code->replace(uniform, code->indexOf(bracket, ';') - uniform + 1, blockCode);
    }
}

Shader::Location::Location(const char *name, int32 index) {
    this->index = index;
    this->name = new char[strlen(name) + 1];
    strcpy(this->name, name);
}

Shader::Location::~Location() { delete[] name; }
