#include "TransportNode.h"

using namespace Silexars;
using namespace System;
using namespace IO;
using namespace Net;
using namespace Transport;

TransportNode::~TransportNode() {}

uint8 TransportNode::getLayer() const { return TRANSPORT; }
