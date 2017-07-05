#include "Message.h"

using namespace Silexars::System::IO;

Message::Listener::~Listener() {
    for (CallbacksMap::iterator it = map.begin(); it != map.end(); it++) {
        std::pair<std::string, Callbacks* > pair = *it;
        delete ((Callbacks*) pair.second);
    }
}

Message::Listener::Callback::Callback(void (*f)(const Message &), void *userData) {
    this->f = f;
    this->userData = userData;
}
void Message::Listener::Callback::operator()(Message &m) {
    m.set("Callback-Data", userData);
    f(m);
}

void Message::Listener::on(const char *message, void (*callback)(const Message&), void* CallbackData) {
    Callbacks* callbacks = map[message];
    if (!callbacks) {
        callbacks = new Callbacks();
        map[message] = callbacks;
    }
    callbacks->push_back(Callback(callback, CallbackData));
}
void Message::Listener::dispatch(const char *messageName) const {
    Message m;
    dispatch(messageName, m);
}

void Message::Listener::dispatch(const char *messageName, Message &message) const {
    Callbacks* callbacks = const_cast<Listener*>(this)->map[messageName];
    if (callbacks)
        for (Callbacks::iterator it = callbacks->begin(); it != callbacks->end(); it++) {
            Callback f = *it;
            f(message);
        }
}
