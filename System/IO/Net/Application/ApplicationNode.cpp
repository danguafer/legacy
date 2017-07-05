#include "ApplicationNode.h"

using namespace Silexars;
using namespace System;
using namespace IO;
using namespace Net;
using namespace Application;

ApplicationNode::~ApplicationNode() {}

uint8 ApplicationNode::getLayer() const { return APPLICATION; }
