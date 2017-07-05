#ifndef SILEXARS_GRAPHICS_FONT_MAP_H
#define SILEXARS_GRAPHICS_FONT_MAP_H

#include "Font.h"
#include <map>

namespace Silexars {
    namespace Graphics {
        class Font::Map {
            public:
                struct Offset { uint32 x, y; };

                Map(Font *font, uint32 *characters);
                ~Map();

                Image* getImage() const;
                Offset getOffset(uint32 character) const;
            private:
                Image* image;
                std::map<uint32, Offset> offsetMap;
        };
    }
}

#endif // FONT_MAP_H
