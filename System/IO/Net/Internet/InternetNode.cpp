#include "InternetNode.h"

using namespace Silexars;
using namespace System;
using namespace IO;
using namespace Net;
using namespace Internet;

InternetNode::~InternetNode() {}
uint8 InternetNode::getLayer() const { return INTERNET; }
