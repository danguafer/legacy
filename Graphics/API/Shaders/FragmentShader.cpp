#include "FragmentShader.h"

#include "../third-party/glLoader/glLoader.h"

using namespace Silexars::Graphics::API::Shaders;

FragmentShader::FragmentShader(const char *source) : Shader(source, GL_FRAGMENT_SHADER) {}
