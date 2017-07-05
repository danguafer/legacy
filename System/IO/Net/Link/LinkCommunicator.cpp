#include "LinkCommunicator.h"

using namespace Silexars;
using namespace System;
using namespace IO;
using namespace Net;
using namespace Link;

LinkCommunicator::LinkCommunicator(LinkNode *node) : NetCommunicator(0, node) {}
LinkCommunicator::~LinkCommunicator() {}

uint8 LinkCommunicator::getLayer() const { return NetNode::LINK; }
