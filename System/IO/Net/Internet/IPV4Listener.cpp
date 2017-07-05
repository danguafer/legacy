#include "IPV4Listener.h"

using namespace Silexars;
using namespace System;
using namespace IO;
using namespace Net;
using namespace Internet;
using namespace Link;

IPV4Listener::IPV4Listener(LinkListener *parent, IPV4Node *node) : InternetListener(parent, node) {}
IPV4Listener::IPV4Listener(IPV4Node *node) : InternetListener(0, node) {}

Communicator* IPV4Listener::accept() { return 0; }

uint8 IPV4Listener::getProtocol() const { return InternetNode::IPV4; }

