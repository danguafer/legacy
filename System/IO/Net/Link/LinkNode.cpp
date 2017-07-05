#include "LinkNode.h"

using namespace Silexars;
using namespace System;
using namespace IO;
using namespace Net;
using namespace Link;

LinkNode::~LinkNode() {}

uint8 LinkNode::getLayer() const { return LINK; }
