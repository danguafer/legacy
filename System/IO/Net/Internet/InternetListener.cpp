#include "InternetListener.h"

using namespace Silexars;
using namespace System;
using namespace IO;
using namespace Net;
using namespace Internet;

InternetListener::InternetListener(Link::LinkListener *parent, InternetNode *node) : NetListener(parent, node) {}
InternetListener::~InternetListener() {}

uint8 InternetListener::getLayer() const { return NetNode::INTERNET; }
