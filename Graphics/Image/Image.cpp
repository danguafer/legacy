#include "Image.h"
#include <cstring>

using namespace Silexars::Graphics;

Image::Image(uint32 width, uint32 height, uint8 channels, uint8 bytesPerChannel, void *data) {
    this->width = width;
    this->height = height;
    this->channels = channels;
    bpc = bytesPerChannel;

    uint32 size = width*height*channels*bpc;
    this->data = new uint8[size];
    memcpy(this->data, data, size);
}

Image::~Image() { delete[] data; }

uint32 Image::getWidth() { return width; }
uint32 Image::getHeight() { return height; }

uint8 Image::getChannels() { return channels; }
uint8 Image::getBPC() { return bpc; }

void *Image::getData() { return data; }

Image* Image::load(const char *path) {
    Image* image = loadPNG(path);
    if (!image) image = loadJPEG(path);
    if (!image) image = loadBMP(path);
    return image;
}

bool Image::save(const char *path, uint8 format) {
    if (getWidth() && getHeight() && getChannels() && getData())
        switch (format) {
            case  PNG: return savePNG(path);
            case JPEG: return saveJPEG(path);
            case  BMP: return saveBMP(path);
        }
    return false;
}

Image* Image::loadJPEG(const char *path) { return 0; }
Image* Image::loadBMP(const char *path) { return 0; }

bool Image::saveJPEG(const char *path) { return false; }
bool Image::saveBMP(const char *path) { return false; }
