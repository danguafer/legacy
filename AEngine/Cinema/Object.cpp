#include "Object.h"

using namespace Silexars;

using namespace Graphics;
using namespace API;
using namespace Buffers;

using namespace AEngine::Cinema;

Object::Object(Material *material, RenderProgram::VertexArrayObject *vao) {
    this->vao = vao;
    this->material = material;
}
Object::~Object() {}

Object::Material* Object::getMaterial() const { return material; }
RenderProgram::VertexArrayObject* Object::getVAO() const { return vao; }

uint8 Object::getType() const { return OBJECT; }
