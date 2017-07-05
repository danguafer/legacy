#include "IPV4Communicator.h"
#include "IPV4Listener.h"

using namespace Silexars;
using namespace System;
using namespace IO;
using namespace Net;
using namespace Internet;

IPV4Communicator::IPV4Communicator(Link::LinkCommunicator *parent, IPV4Node *node) : InternetCommunicator(parent, node) {}
IPV4Communicator::IPV4Communicator(IPV4Listener *listener, Link::LinkCommunicator *parent, IPV4Node *node) : InternetCommunicator(listener, parent, node) {}
IPV4Communicator::IPV4Communicator(IPV4Node *node) : InternetCommunicator(0, node) {}
IPV4Communicator::IPV4Communicator(IPV4Listener *listener, IPV4Node *node) : InternetCommunicator(listener, 0, node) {}

uint8 IPV4Communicator::getStatus() const { return DISCONNECTED; }

uint32 IPV4Communicator::write(const void *data, uint32 size) { return 0; }
uint32 IPV4Communicator::read(void *data, uint32 size) { return 0; }
uint32 IPV4Communicator::peek(void *data, uint32 size) const { return 0; }

uint32 IPV4Communicator::canWrite() const { return 0; }
uint32 IPV4Communicator::canRead() const { return 0; }

uint8 IPV4Communicator::getProtocol() const { return InternetNode::IPV4; }
