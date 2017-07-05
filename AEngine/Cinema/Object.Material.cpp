#include "Object.Material.h"

using namespace Silexars;
using namespace AEngine;
using namespace Cinema;

using namespace Graphics;
using namespace API::Samplers;

Object::Material::Material(Sampler2D *albedo) {
    this->albedo = albedo;
}

Sampler2D* Object::Material::getAlbedo() const { return albedo; }
