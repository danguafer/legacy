#include "ApplicationCommunicator.h"

using namespace Silexars;
using namespace System;
using namespace IO;
using namespace Net;
using namespace Application;
using namespace Transport;

ApplicationCommunicator::ApplicationCommunicator(TransportCommunicator *parent, ApplicationNode *node) : NetCommunicator(parent, node) {}
ApplicationCommunicator::~ApplicationCommunicator() {}

uint8 ApplicationCommunicator::getLayer() const { return NetNode::APPLICATION; }
