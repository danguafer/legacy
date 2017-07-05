#include "File.h"
#include <cstdio>

using namespace Silexars::System::IO::FileSystem;

#ifndef ANDROID
File::File(FileNode *node) : Communicator(node) { id = (Handle) fopen(node->getPath(), "rb+"); }
#endif
File::~File() { if (id) fclose((::FILE*) id); }

uint32 File::write(const void *data, uint32 size) {
    uint32 ret = fwrite(data, 1, size, (::FILE*) id);
    if (ret <= 0) return 0;
    return ret;
}

uint32 File::read(void *data, uint32 size) {
    uint32 ret = fread(data, 1, size, (::FILE*) id);
    if (ret <= 0) return 0;
    return ret;
}

uint32 File::peek(void *data, uint32 size) const {
    uint32 position = getPosition();
    uint32 ret = const_cast<File*>(this)->read(data, size);
    const_cast<File*>(this)->setPosition(position);
    return ret;
}

void File::setPosition(uint32 position) { fseek((::FILE*) id, position, SEEK_SET); }
uint32 File::getPosition() const { return ftell((::FILE*) id); }

uint32 File::getSize() const { // non-portable, they say.
    uint32 position = getPosition();
    fseek((::FILE*) id, 0, SEEK_END);
    uint32 size = ftell((::FILE*) id);
    const_cast<File*>(this)->setPosition(position);
    return size;
}

uint8 File::getCommunicatorType() const { return Node::FILE; }

uint8 File::getStatus() const { return id ? CONNECTED : DISCONNECTED; }

uint32 File::canRead() const { return id ? getSize() - getPosition() : 0; }
uint32 File::canWrite() const { return id ? 1024*1024 : 0; }

FILE* File::getFILE() const { return (FILE*) id; }
