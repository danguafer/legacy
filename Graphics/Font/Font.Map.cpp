#include "Font.Map.h"
#include <cstdlib>
#include <iostream>
#include <ft2build.h>
#include FT_FREETYPE_H
#include <Veritas/etc/LogService/LogService.h>

using Veritas::etc::LogService;

using namespace Silexars;
using namespace Graphics;
using namespace Math;

inline void copy(uint8* out, uint32 ox, uint32 oy, uint32 ow, uint32 oh, uint8* in, uint32 iw, uint32 ih) {
    for (uint32 i = 0; i < ih; i++) {
        uint8 *segi = &in[i * iw];
        uint8 *sego = &out[(i + oy) * ow + ox];

        memcpy(sego, segi, iw);
    }
}

Font::Map::Map(Font *font, uint32 *characters) {
    uint32 width = 512;
    uint32 height = 512;
    uint8* bitmap = new uint8[width * height];
    memset(bitmap, 0, width * height);

    uint32 x = 0, y = 0;
    uint32 my = 0;

    for (uint32 i = 0; characters[i]; i++) {
        Font::Glyph *g = font->getGlyph(characters[i], true);
        if (g && g->getImage()) {
            uint32 iw = g->getImage()->getWidth();
            uint32 ih = g->getImage()->getHeight();
            if (x + iw > width) {
                y += my + 1;
                x = my = 0;
            }
            if (ih > my) my = ih;
            if (y + ih > height) {
                LogService::error("Not enough space for storing the atlas");
                break;
            }

            Offset offset = { x, y };
            offsetMap[characters[i]] = offset;
            copy(bitmap, x, y, width, height, (uint8*) g->getImage()->getData(), iw, ih);
            x += iw + 1;
        }
        delete g;
    }

    image = new Image(width, height, 1, 1, bitmap);

    delete[] bitmap;
}

Font::Map::~Map() { delete image; }

Image* Font::Map::getImage() const { return image; }

Font::Map::Offset Font::Map::getOffset(uint32 c) const { return const_cast<Map*>(this)->offsetMap[c]; }
