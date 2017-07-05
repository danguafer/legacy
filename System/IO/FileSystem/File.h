#ifndef SILEXARS_SYSTEM_IO_FILESYSTEM_FILE_H_
#define SILEXARS_SYSTEM_IO_FILESYSTEM_FILE_H_

#include "FileNode.h"
#include "../Communicator.h"
#include <cstdio>

namespace Silexars {
    namespace System {
        namespace IO {
            namespace FileSystem {
                class File : public Communicator {
                    public:
                        File(FileNode *node);
                        ~File();

                        uint8 getCommunicatorType() const;

                        uint8 getStatus() const;

                        uint32 write(const void *data, uint32 size);
                        uint32 read(void *data, uint32 size);
                        uint32 peek(void *data, uint32 size) const;

                        uint32 canWrite() const;
                        uint32 canRead() const;

                        void setPosition(uint32 position);
                        uint32 getPosition() const;

                        uint32 getSize() const;

                        FILE* getFILE() const;
                    private:
                        Handle id;
                };
            }
        }
    }
}

#endif
