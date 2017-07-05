#include "InternetCommunicator.h"
#include "InternetListener.h"

using namespace Silexars;
using namespace System;
using namespace IO;
using namespace Net;
using namespace Internet;
using namespace Link;

InternetCommunicator::InternetCommunicator(LinkCommunicator *parent, InternetNode *node) : NetCommunicator(parent, node) {}
InternetCommunicator::InternetCommunicator(InternetListener *listener, LinkCommunicator *parent, InternetNode *node) : NetCommunicator(listener, parent, node) {}
InternetCommunicator::~InternetCommunicator() {}

uint8 InternetCommunicator::getLayer() const { return NetNode::INTERNET; }
