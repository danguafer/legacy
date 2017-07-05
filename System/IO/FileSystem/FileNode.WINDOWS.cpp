#include <Veritas/Definitions/Definitions.h>
#ifdef WINDOWS

#include "FileNode.h"
#include <windows.h>
#include <sys/stat.h>

using namespace Silexars::System::IO::FileSystem;

void FileNode::systemCreateFileNode(const char *path) {
    if (!GetFullPathName(path, 1024, this->path, 0)) strcpy(this->path, path); // If any error occurs, we use the relative path instead

    struct stat st;
    stat(path, &st);
    type = S_ISDIR(st.st_mode) ? FileNode::DIRECTORY : FileNode::FILE;
}

#endif
