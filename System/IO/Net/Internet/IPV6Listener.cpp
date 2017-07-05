#include "IPV6Listener.h"

using namespace Silexars;
using namespace System;
using namespace IO;
using namespace Net;
using namespace Internet;
using namespace Link;

IPV6Listener::IPV6Listener(LinkListener *parent, IPV6Node *node) : InternetListener(parent, node) {}
IPV6Listener::IPV6Listener(IPV6Node *node) : InternetListener(0, node) {}

Communicator* IPV6Listener::accept() { return 0; }

uint8 IPV6Listener::getProtocol() const { return InternetNode::IPV6; }

