#include "ComputeShader.h"
#include "../third-party/glLoader/glLoader.h"

using namespace Silexars::Graphics::API::Shaders;

ComputeShader::ComputeShader(const char *source) : Shader(source, GL_COMPUTE_SHADER) {}
