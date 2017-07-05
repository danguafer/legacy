#include "IPV6Communicator.h"
#include "IPV6Listener.h"

using namespace Silexars;
using namespace System;
using namespace IO;
using namespace Net;
using namespace Internet;

IPV6Communicator::IPV6Communicator(Link::LinkCommunicator *parent, IPV6Node *node) : InternetCommunicator(parent, node) {}
IPV6Communicator::IPV6Communicator(IPV6Listener *listener, Link::LinkCommunicator *parent, IPV6Node *node) : InternetCommunicator(listener, parent, node) {}
IPV6Communicator::IPV6Communicator(IPV6Node *node) : InternetCommunicator(0, node) {}
IPV6Communicator::IPV6Communicator(IPV6Listener *listener, IPV6Node *node) : InternetCommunicator(listener, 0, node) {}

uint8 IPV6Communicator::getStatus() const { return DISCONNECTED; }

uint32 IPV6Communicator::write(const void *data, uint32 size) { return 0; }
uint32 IPV6Communicator::read(void *data, uint32 size) { return 0; }
uint32 IPV6Communicator::peek(void *data, uint32 size) const { return 0; }

uint32 IPV6Communicator::canWrite() const { return 0; }
uint32 IPV6Communicator::canRead() const { return 0; }

uint8 IPV6Communicator::getProtocol() const { return InternetNode::IPV6; }
