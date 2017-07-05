#include "Camera.h"

using namespace Silexars;
using namespace AEngine::Cinema;

using namespace Graphics::API::Buffers;

Camera::Camera() {
    ubo = new UniformBuffer("vec3 cameraPosition; mat4 worldToCamera; mat4 cameraToScreen;");
}

Camera::~Camera() {
    delete ubo;
}

uint8 Camera::getType() const { return CAMERA; }
