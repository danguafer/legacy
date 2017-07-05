#include "Font.Glyph.h"

using namespace Silexars::Graphics;

#include <cstdlib>

Font::Glyph::Glyph(uint32 width, uint32 height, uint32 bearingx, uint32 bearingy, uint32 advance, uint8 *bitmap) {
    this->width = width;
    this->height = height;
    this->bearingx = bearingx;
    this->bearingy = bearingy;
    this->advance = advance / 64;

    if (bitmap) image = new Image(width, height, 1, 1, bitmap);
    else image = 0;
}
Font::Glyph::~Glyph() { delete image; }

uint32 Font::Glyph::getWidth() const { return width; }
uint32 Font::Glyph::getHeight() const { return height; }
int32 Font::Glyph::getBearingX() const { return bearingx; }
int32 Font::Glyph::getBearingY() const { return bearingy; }
uint32 Font::Glyph::getAdvance() const { return advance; }

Image* Font::Glyph::getImage() const { return image; }
