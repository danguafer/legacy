#include "GeometryShader.h"

#include "../third-party/glLoader/glLoader.h"

using namespace Silexars::Graphics::API::Shaders;

GeometryShader::GeometryShader(const char *source) : Shader(source, GL_GEOMETRY_SHADER) {}
