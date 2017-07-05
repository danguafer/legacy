#include "Listener.h"

using namespace Silexars;
using namespace System;
using namespace IO;

Listener::Listener(Node *node) {
    this->node = node;
    islistening = false;
}
Listener::~Listener() {}

bool Listener::isListening() const { return islistening; }

Node* Listener::getNode() const { return node; }

void Listener::manage() {
    for (Communicators::iterator it = communicators.begin(); it != communicators.end();) {
        Communicator *c = *(it++);
        c->manage();
    }

    Communicator *c = accept();
    if (c) {
        communicators.push_back(c);
        Message().set("Communicator", c).dispatch(this, "Connection");
    }
}
