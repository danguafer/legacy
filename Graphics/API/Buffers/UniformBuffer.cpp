#include "UniformBuffer.h"
#include "UniformBuffer.Local.h"
#include "UniformBuffer.Fallback.h"

using namespace Silexars;
using namespace Graphics::API;
using namespace Buffers;

UniformBuffer::UniformBuffer(const char *source) { ubimpl = new Fallback(source); }
UniformBuffer::UniformBuffer(Program *program) { ubimpl = new Local(program); }
UniformBuffer::~UniformBuffer() { delete ubimpl; }

bool UniformBuffer::isValid() const { return ubimpl->isValid(); }
const char* UniformBuffer::getMessage() const { return ubimpl->getMessage(); }
const char* UniformBuffer::getSource() const { return ubimpl->getSource(); }

int32 UniformBuffer::getUniformLocation(const char *uniform) const { ubimpl->getUniformLocation(uniform); }
void UniformBuffer::uniform(int32 location, float32* value) { ubimpl->uniform(location, value); }
void UniformBuffer::uniform(int32 location, int32* value) { ubimpl->uniform(location, value); }
void UniformBuffer::uniform(int32 location, uint32* value) { ubimpl->uniform(location, value); }
void UniformBuffer::uniform(int32 location, float32 value) { ubimpl->uniform(location, value); }
void UniformBuffer::uniform(int32 location, int32 value) { ubimpl->uniform(location, value); }
void UniformBuffer::uniform(int32 location, uint32 value) { ubimpl->uniform(location, value); }
void UniformBuffer::uniform2(int32 location, float32 *value) { ubimpl->uniform2(location, value); }
void UniformBuffer::uniform2(int32 location, int32 *value) { ubimpl->uniform2(location, value); }
void UniformBuffer::uniform2(int32 location, uint32 *value) { ubimpl->uniform2(location, value); }
void UniformBuffer::uniform3(int32 location, float32 *value) { ubimpl->uniform3(location, value); }
void UniformBuffer::uniform3(int32 location, int32 *value) { ubimpl->uniform3(location, value); }
void UniformBuffer::uniform3(int32 location, uint32 *value) { ubimpl->uniform3(location, value); }
void UniformBuffer::uniform4(int32 location, float32 *value) { ubimpl->uniform4(location, value); }
void UniformBuffer::uniform4(int32 location, int32 *value) { ubimpl->uniform4(location, value); }
void UniformBuffer::uniform4(int32 location, uint32 *value) { ubimpl->uniform4(location, value); }
void UniformBuffer::uniform2x2(int32 location, float32 *value) { ubimpl->uniform2x2(location, value); }
void UniformBuffer::uniform3x3(int32 location, float32 *value) { ubimpl->uniform3x3(location, value); }
void UniformBuffer::uniform4x4(int32 location, float32 *value) { ubimpl->uniform4x4(location, value); }

void UniformBuffer::bindTo(API::Program *program) { ubimpl->bindTo(program); }
void UniformBuffer::unbindFrom(API::Program *program) { ubimpl->unbindFrom(program); }
