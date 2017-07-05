#include "EthernetCommunicator.h"

using namespace Silexars;
using namespace System;
using namespace IO;
using namespace Net;
using namespace Link;

EthernetCommunicator::EthernetCommunicator(EthernetNode *node) : LinkCommunicator(node) {}

uint8 EthernetCommunicator::getStatus() const { return DISCONNECTED; }

uint32 EthernetCommunicator::write(void *data, uint32 size) { return 0; }
uint32 EthernetCommunicator::read(void *data, uint32 size) { return 0; }
uint32 EthernetCommunicator::peek(void *data, uint32 size) const { return 0; }

uint32 EthernetCommunicator::canWrite() const { return 0; }
uint32 EthernetCommunicator::canRead() const { return 0; }

uint8 EthernetCommunicator::getProtocol() const { return LinkNode::ETHERNET; }
