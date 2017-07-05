//!Complete
#include <Veritas/Definitions/Definitions.h>
#ifdef POSIX

#include "Directory.h"

using namespace Silexars;
using namespace System;
using namespace IO;
using namespace FileSystem;

#include <cstring>
#include <dirent.h>

void Directory::systemCreateDirectory(const char *path) {
    id = (Handle) opendir(path);
}

void Directory::systemUpdate() {
    if (!id) return;

    iterate(List, &list) delete *iterator;
    uint32 dirlen = strlen(node->getPath());

    dirent *ent;
    for (dirent *ent; (ent = readdir((DIR*) id)); )
        if (strcmp(ent->d_name, ".") && strcmp(ent->d_name, "..")) {
            uint32 len = dirlen + strlen(ent->d_name) + 2;
            char* s = new char[len];
            strcpy(s, node->getPath());
            if (s[dirlen - 1] != '/') strcat(s, "/");
            strcat(s, ent->d_name);

            list.push_back(new FileNode(s));

            delete[] s;
        }
}

void Directory::systemDestroyDirectory() { closedir((DIR*) id); }

#endif
