#include "TransportListener.h"

using namespace Silexars;
using namespace System;
using namespace IO;
using namespace Net;
using namespace Transport;

TransportListener::TransportListener(Internet::InternetListener *parent, TransportNode *node) : NetListener(parent, node) {}
TransportListener::~TransportListener() {}

uint8 TransportListener::getLayer() const { return NetNode::TRANSPORT; }
