#include "VertexShader.h"
#include "../third-party/glLoader/glLoader.h"
#include <cstring>

using namespace Silexars::Graphics::API;
using namespace Shaders;

VertexShader::VertexShader(const char *source) : Shader(source, GL_VERTEX_SHADER) {}
