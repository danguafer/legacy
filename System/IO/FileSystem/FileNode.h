//!Complete

#ifndef SILEXARS_SYSTEM_IO_FILESYSTEM_FILENODE_H_
#define SILEXARS_SYSTEM_IO_FILESYSTEM_FILENODE_H_

#include "../Node.h"

namespace Silexars {
    namespace System {
        namespace IO {
            namespace FileSystem {
                class FileNode : public Node {
                    public:
                        FileNode(const char *path);
                        ~FileNode();

                        static bool create(const char *path, uint32 type);

                        const char* getPath() const;

                        uint8 getNodeType() const;
                        uint8 getFileNodeType() const;

                        bool static exists(const char *path);

                        enum TYPES { FILE, DIRECTORY };
                    protected:
                        uint8 type;
                        char path[1024];

                        void systemCreateFileNode(const char *path);
                };
            }
        }
    }
}

#endif
