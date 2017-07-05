#include "ApplicationListener.h"

using namespace Silexars;
using namespace System;
using namespace IO;
using namespace Net;
using namespace Application;

ApplicationListener::ApplicationListener(Transport::TransportListener *parent, ApplicationNode *node) : NetListener(parent, node) {}
ApplicationListener::~ApplicationListener() {}

uint8 ApplicationListener::getLayer() const { return NetNode::APPLICATION; }
