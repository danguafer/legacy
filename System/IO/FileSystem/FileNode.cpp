#include "FileNode.h"
#include "Directory.h"
#include "File.h"

#include <cstdio>

using namespace Silexars::System::IO::FileSystem;

FileNode::FileNode(const char *path) { systemCreateFileNode(path); }
FileNode::~FileNode() {}

const char* FileNode::getPath() const { return path; }

uint8 FileNode::getNodeType() const { return Node::FILE; }
uint8 FileNode::getFileNodeType() const { return type; }

bool FileNode::create(const char *path, uint32 type) {
    if (type == FILE) {
        ::FILE *fp = fopen(path, "w");
        if (fp) {
            fclose(fp);
            return true;
        } else return false;
    } else return false;
}
