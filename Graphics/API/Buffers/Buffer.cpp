#include "Buffer.h"
#include "../third-party/glLoader/glLoader.h"

using namespace Silexars::Graphics::API::Buffers;

Buffer::Buffer() { glGenBuffers(1, (GLuint*) &id); }
Buffer::~Buffer() { glDeleteBuffers(1, (GLuint*) &id); }
