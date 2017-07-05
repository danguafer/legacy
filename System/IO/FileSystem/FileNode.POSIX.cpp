#include <Veritas/Definitions/Definitions.h>
#ifdef POSIX

#include "FileNode.h"
#include <stdlib.h>
#include <sys/stat.h>
#include <cstring>

using namespace Silexars::System::IO::FileSystem;

void FileNode::systemCreateFileNode(const char *ppath) {
    char *path = ppath[0] ? (char*) ppath : (char*) ".";
    if (!realpath(path, this->path)) strcpy(this->path, path); // If any error occurs, we use the relative path instead

    struct stat st;
    stat(path, &st);
    type = S_ISDIR(st.st_mode) ? FileNode::DIRECTORY : FileNode::FILE;
}

#endif
