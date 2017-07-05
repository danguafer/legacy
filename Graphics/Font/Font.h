#pragma once

#include <Veritas/Definitions/Definitions.h>
#include <Veritas/Graphics/Image/Image.h>
#include <Veritas/Math/Math.h>

namespace Silexars {
    namespace Graphics {
        class Font {
            public:
                class Glyph;
                class Map;

                static Font* load(const char *path);
                ~Font();

                void setHeight(uint32 height);
                uint32 getHeight() const;

                Glyph* getGlyph(uint32 character, bool renderImage = false) const;

                Math::vec2 measureText(const char* text, float32 height, Math::vec2* offset = 0) const;
            private:
                Font(const char *path);

                uint32 height;

                void *pimpl;

        };
    }
}

#include "Font.Glyph.h"
#include "Font.Map.h"
