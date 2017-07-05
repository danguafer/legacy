#pragma once

#include "Font.h"
#include <Veritas/Math/Math.h>

namespace Silexars {
    namespace Graphics {
        class Font::Glyph {
            public:
                Image* getImage() const;

                uint32 getWidth() const;
                uint32 getHeight() const;
                int32 getBearingX() const;
                int32 getBearingY() const;
                uint32 getAdvance() const;

                ~Glyph();
            private:
                friend class Font;

                Glyph(uint32 width, uint32 height, uint32 bearingx, uint32 bearingy, uint32 advance, uint8 *bitmap);

                uint32 width, height, advance;
                int32 bearingx, bearingy;
                Image *image;
        };
    }
}
