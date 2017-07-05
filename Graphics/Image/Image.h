#pragma once

typedef unsigned char uint8;
typedef int int32;
typedef unsigned int uint32;

namespace Silexars {
    namespace Graphics {
        class Image {
            public:
                Image(uint32 width, uint32 height, uint8 channels, uint8 bytesPerChannel, void* data);
                ~Image();

                uint32 getWidth();
                uint32 getHeight();

                uint8 getChannels();
                uint8 getBPC();

                void* getData();

                static Image* load(const char *path);
                bool save(const char *path, uint8 format);
                enum SAVE_FORMAT { BMP, JPEG, PNG };
            private:
                uint32 width, height;
                uint8 channels;
                uint8 bpc;
                uint8* data;

                bool savePNG(const char *path);
                bool saveJPEG(const char *path);
                bool saveBMP(const char *path);
                static Image* loadPNG(const char *path);
                static Image* loadJPEG(const char *path);
                static Image* loadBMP(const char *path);
        };
    }
}
