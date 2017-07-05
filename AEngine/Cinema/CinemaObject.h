#pragma once

#include <Veritas/Definitions/Definitions.h>
#include <Veritas/Math/Math.h>

namespace Silexars {
    namespace AEngine {
        namespace Cinema {
            class CinemaObject {
                public:
                    CinemaObject();
                    virtual ~CinemaObject();

                    void setName(const char *name);
                    const char* getName() const;

                    void setPosition(const Math::vec3& position);
                    Math::vec3 getPosition() const;

                    void setRotation(const Math::vec3& eulerAngles);
                    void setRotation(const Math::Quaternion &rotation);
                    Math::Quaternion getRotation() const;

                    void setScale(const Math::vec3& scale);
                    Math::vec3 getScale() const;

                    void lookAt(const Math::vec3 &position, const Math::vec3& up);

                    virtual uint8 getType() const = 0;
                    enum TYPES { UNKNOWN, CAMERA, SCENE, LIGHT, OBJECT };
                public:
                    char *name;

                    Math::vec3 position, scale;
                    Math::Quaternion rotation;
            };
        }
    }
}
