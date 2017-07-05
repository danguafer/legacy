#include "LinkListener.h"

using namespace Silexars;
using namespace System;
using namespace IO;
using namespace Net;
using namespace Link;

LinkListener::LinkListener(LinkNode *node) : NetListener(0, node) {}
LinkListener::~LinkListener() {}

uint8 LinkListener::getLayer() const { return NetNode::LINK; }
