#include "UniformBuffer.Local.h"

#include "../Program.h"
#include "../third-party/glLoader/glLoader.h"

using namespace Silexars::Graphics::API;
using namespace Buffers;

UniformBuffer::Local::Local(Program *program) { this->program = program; }

bool UniformBuffer::Local::isValid() const { return program->isValid(); }
const char* UniformBuffer::Local::getMessage() const { return program->getMessage(); }
const char* UniformBuffer::Local::getSource() const { return (const char*) ""; }

int32 UniformBuffer::Local::getUniformLocation(const char *uniform) const { return glGetUniformLocation((GLuint) program->id, uniform); }

void UniformBuffer::Local::uniform(int32 location, float32* value) { uniform(location, *value); }
void UniformBuffer::Local::uniform(int32 location, int32* value) { uniform(location, *value); }
void UniformBuffer::Local::uniform(int32 location, uint32* value) { uniform(location, *value); }

void UniformBuffer::Local::uniform(int32 location, float32 value) { program->use(); glUniform1f(location, value); }
void UniformBuffer::Local::uniform(int32 location, int32 value) { program->use(); glUniform1i(location, value); }
void UniformBuffer::Local::uniform(int32 location, uint32 value) { program->use(); glUniform1ui(location, value); }
void UniformBuffer::Local::uniform2(int32 location, float32* value) { program->use(); glUniform2fv(location, 1, (GLfloat*) value); }
void UniformBuffer::Local::uniform2(int32 location, int32* value) { program->use(); glUniform2iv(location, 1, (GLint*) value); }
void UniformBuffer::Local::uniform2(int32 location, uint32* value) { program->use(); glUniform2uiv(location, 1, (GLuint*) value); }
void UniformBuffer::Local::uniform3(int32 location, float32* value) { program->use(); glUniform3fv(location, 1, (GLfloat*) value); }
void UniformBuffer::Local::uniform3(int32 location, int32* value) { program->use(); glUniform3iv(location, 1, (GLint*) value); }
void UniformBuffer::Local::uniform3(int32 location, uint32* value) { program->use(); glUniform3uiv(location, 1, (GLuint*) value); }
void UniformBuffer::Local::uniform4(int32 location, float32* value) { program->use(); glUniform4fv(location, 1, (GLfloat*) value); }
void UniformBuffer::Local::uniform4(int32 location, int32* value) { program->use(); glUniform4iv(location, 1, (GLint*) value); }
void UniformBuffer::Local::uniform4(int32 location, uint32* value) { program->use(); glUniform4uiv(location, 1, (GLuint*) value); }
void UniformBuffer::Local::uniform2x2(int32 location, float32 *value) { program->use(); glUniformMatrix2fv(location, 1, false, (GLfloat*) value); }
void UniformBuffer::Local::uniform3x3(int32 location, float32 *value) { program->use(); glUniformMatrix3fv(location, 1, false, (GLfloat*) value); }
void UniformBuffer::Local::uniform4x4(int32 location, float32 *value) { program->use(); glUniformMatrix4fv(location, 1, false, (GLfloat*) value); }

void UniformBuffer::Local::bindTo(Program *program) {}
void UniformBuffer::Local::unbindFrom(Program *program) {}
