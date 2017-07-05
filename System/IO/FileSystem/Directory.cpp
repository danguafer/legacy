#include "Directory.h"

using namespace Silexars::System::IO;
using namespace FileSystem;


Directory::Directory(FileNode *node) {
    if (node->getFileNodeType() == FileNode::DIRECTORY) {
        this->node = node;
        systemCreateDirectory(node->getPath());
    } else {
        node = 0;
        id = 0;
    }
}

Directory::~Directory() {
    iterate(List, &list) delete *iterator;
    if (id) systemDestroyDirectory();
}

Directory::iterator Directory::begin() { systemUpdate(); return list.begin(); }
Directory::iterator Directory::end() { return list.end(); }
uint32 Directory::size() const { return list.size(); }
