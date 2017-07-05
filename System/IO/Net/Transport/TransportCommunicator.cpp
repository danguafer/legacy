#include "TransportCommunicator.h"
#include "TransportListener.h"

using namespace Silexars;
using namespace System;
using namespace IO;
using namespace Net;
using namespace Transport;
using namespace Internet;

TransportCommunicator::TransportCommunicator(InternetCommunicator *parent, TransportNode *node) : NetCommunicator(parent, node) {}
TransportCommunicator::TransportCommunicator(TransportListener *listener, InternetCommunicator *parent, TransportNode *node) : NetCommunicator(listener, parent, node) {}
TransportCommunicator::~TransportCommunicator() {}

uint8 TransportCommunicator::getLayer() const { return NetNode::TRANSPORT; }
