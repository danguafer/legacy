#include "Image.h"

#include <png.h>

#warning Remove some post-processing functionalities e.g. png_set_strip_16, etc
#warning It is always converting n-channels format to a 4-channels format

#include <Veritas/System/IO/FileSystem/FileSystem.h>

using namespace Silexars;
using namespace Graphics;
using namespace System::IO::FileSystem;

Image* Image::loadPNG(const char *path) {
    FileNode node(path);
    File file(&node);
    if (file.getStatus() == File::DISCONNECTED) return 0;

    uint8 header[8];

    fread(header, sizeof(header), 1, file.getFILE());
    if (png_sig_cmp(header,0,sizeof(header))) return 0;

    png_structp png;
    png_infop info;

    png = png_create_read_struct(PNG_LIBPNG_VER_STRING,0,0,0);

    if (!png) return 0;
    info = png_create_info_struct(png);
    if (!info) {
        png_destroy_read_struct(&png,0,0);
        return 0;
    }

    png_init_io(png, file.getFILE());
    png_set_sig_bytes(png, sizeof(header));

    png_read_info(png,info);

    int32 bitdepth, colortype;
    png_uint_32 width, height;
    png_get_IHDR(png,info,&width, &height, &bitdepth, &colortype, 0, 0, 0);

    double wx,wy,rx,ry,gx,gy,bx,by;
    png_get_cHRM(png, info, &wx, &wy, &rx, &ry, &gx, &gy, &bx, &by);

    if (colortype == PNG_COLOR_TYPE_PALETTE) png_set_palette_to_rgb(png);
    if (colortype == PNG_COLOR_TYPE_GRAY && bitdepth < 8) png_set_expand_gray_1_2_4_to_8(png);
    if (colortype == PNG_COLOR_TYPE_GRAY || colortype == PNG_COLOR_TYPE_GRAY_ALPHA) png_set_gray_to_rgb(png);
    if (png_get_valid(png, info, PNG_INFO_tRNS)) png_set_tRNS_to_alpha(png);
    if (colortype == PNG_COLOR_TYPE_RGB) png_set_filler(png, 0xff, PNG_FILLER_AFTER);
    if (bitdepth == 16) png_set_strip_16(png);
    if (bitdepth < 8) png_set_packing(png);

    static png_byte chunks_to_ignore[] = {
         99,  72,  82,  77, '\0',  /* cHRM */
        104,  73,  83,  84, '\0',  /* hIST */
        105,  67,  67,  80, '\0',  /* iCCP */
        105,  84,  88, 116, '\0',  /* iTXt */
        111,  70,  70, 115, '\0',  /* oFFs */
        112,  67,  65,  76, '\0',  /* pCAL */
        112,  72,  89, 115, '\0',  /* pHYs */
        115,  66,  73,  84, '\0',  /* sBIT */
        115,  67,  65,  76, '\0',  /* sCAL */
        115,  80,  76,  84, '\0',  /* sPLT */
        115,  84,  69,  82, '\0',  /* sTER */
        116,  69,  88, 116, '\0',  /* tEXt */
        116,  73,  77,  69, '\0',  /* tIME */
        122,  84,  88, 116, '\0'   /* zTXt */
    };

    png_set_keep_unknown_chunks(png, 1, chunks_to_ignore, sizeof(chunks_to_ignore)/5);

    png_read_update_info(png,info);
    png_get_IHDR(png,info, &width, &height, &bitdepth, &colortype, 0, 0, 0);

    uint8 channels = png_get_channels(png,info);

    int32 rowbytes = png_get_rowbytes(png,info);

    uint8* data = new uint8[rowbytes*height];
    png_bytep *row_pointers = new png_bytep[height*sizeof(png_bytep)];
    for (uint32 i = 0; i < height; i++) row_pointers[i] = data + i*rowbytes;

    png_read_image(png, row_pointers);
    png_read_end(png, 0);

    png_destroy_read_struct(&png, &info, 0);

    delete[] row_pointers;

    Image *image = new Image(width, height, channels, bitdepth/8, data);
    delete[] data;

    return image;
}

bool Image::savePNG(const char *path) {
    FILE *fp = fopen(path, "wb");
    if (!fp) return false;

    png_structp png = png_create_write_struct(PNG_LIBPNG_VER_STRING, 0, 0, 0);
    png_infop info = png_create_info_struct(png);
    png_init_io(png, fp);

    uint32 type;
    switch (channels) {
        case 1: type = PNG_COLOR_TYPE_GRAY; break;
        case 2: type = PNG_COLOR_TYPE_GA; break;
        case 3: type = PNG_COLOR_TYPE_RGB; break;
        case 4: type = PNG_COLOR_TYPE_RGBA; break;
    }

    png_set_IHDR(png, info, width, height, bpc*8, type, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);
    png_write_info(png, info);

    png_bytepp rowPtrs = new png_bytep[height];
    uint32 stride = width*channels*bpc;
    uint8 *cdata = data;
    for (uint32 i = 0; i < height; i++) {
        rowPtrs[i] = (png_bytep) cdata;
        cdata += stride;
    }

    png_write_image(png, rowPtrs);
    png_write_end(png, 0);

    fclose(fp);
    delete[] rowPtrs;

    return true;
}
