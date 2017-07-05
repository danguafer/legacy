#include "Font.h"
#include <iostream>
#include <ft2build.h>
#include FT_FREETYPE_H
#include <Veritas/etc/LogService/LogService.h>

using namespace Silexars;
using namespace Graphics;
using namespace Math;

using Veritas::etc::LogService;

static uint32 references = 0;
FT_Library ft;

Font::Font(const char *path) {
    if (!references++) FT_Init_FreeType(&ft);

    pimpl = new FT_Face;
    if (FT_New_Face(ft, path, 0, (FT_Face*) pimpl)) LogService::error("Load Font Face error");

    setHeight(16);
}

Font::~Font() {
    FT_Done_Face(*((FT_Face*) pimpl));

    if (!--references) FT_Done_FreeType(ft);
}

Font* Font::load(const char *path) {
    FILE *fp = fopen(path, "rb");
    if (fp) {
        fclose(fp);
        return new Font(path);
    }
    return 0;
}

void Font::setHeight(uint32 height) {
    this->height = height;
    FT_Set_Pixel_Sizes(*(FT_Face*) pimpl, 0, height);
}
uint32 Font::getHeight() const { return height; }

Font::Glyph* Font::getGlyph(uint32 character, bool render) const {
    FT_Face *face = (FT_Face*) pimpl;
    if (!FT_Get_Char_Index(*face, character) || FT_Load_Char(*face, character, FT_LOAD_RENDER))
        return character == ' ' ? 0 : getGlyph(' ');

    return new Glyph((*face)->glyph->bitmap.width, (*face)->glyph->bitmap.rows, (*face)->glyph->bitmap_left, (*face)->glyph->bitmap_top, (*face)->glyph->advance.x, (*face)->glyph->bitmap.buffer);
}

vec2 Font::measureText(const char *text, float32 height, vec2 *offset) const {
    vec2 carriage = vec2(0.0);
    float32 scalef = height/(float32) getHeight();

    vec2 p0(INFINITY), p1(0.0);
    uint32 c;
    for (uint32 i = 0; (c = text[i]); i++) {
        Font::Glyph* g = getGlyph(c);
        if (!g) continue;
        vec2 dimension = vec2(g->getWidth(), g->getHeight()) * scalef;
        vec2 bearing = vec2((int32) g->getBearingX(), - (int32) g->getBearingY()) * scalef;

        vec2 position = bearing + carriage;
        p0 = min(p0, position);
        p1 = max(p1, position + dimension);

        carriage.x += g->getAdvance() * scalef;
        delete g;
    }

    if (p0 == vec2(INFINITY)) p0 = vec2(0.0);
    if (offset) *offset = p0;
    return p1 - p0;
}
