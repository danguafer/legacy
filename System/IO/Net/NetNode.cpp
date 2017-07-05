#include "NetNode.h"

using namespace Silexars;
using namespace System;
using namespace IO;
using namespace Net;

NetNode::~NetNode() {}
uint8 NetNode::getNodeType() const { return NET; }
