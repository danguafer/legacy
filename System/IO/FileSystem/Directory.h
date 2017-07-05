//!Complete

#ifndef SILEXARS_MANAGEMENT_IO_FILESYSTEM_DIRECTORY_H_
#define SILEXARS_MANAGEMENT_IO_FILESYSTEM_DIRECTORY_H_

#include "FileNode.h"
#include <list>

namespace Silexars {
    namespace System {
        namespace IO {
            namespace FileSystem {
                class Directory {
                    private:
                        typedef std::list<FileNode*> List;
                    public:
                        typedef List::iterator iterator;

                        Directory(FileNode *node);
                        ~Directory();

                        iterator begin();
                        iterator end();
                        uint32 size() const;

                        static bool create(const char *path);
                    private:
                        FileNode *node;
                        List list;
                        Handle id;

                        void systemCreateDirectory(const char *path);
                        void systemDestroyDirectory();
                        void systemUpdate();
                };
            }
        }
    }
}

#endif
