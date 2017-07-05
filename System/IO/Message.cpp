#include "Message.h"

using namespace Silexars::System::IO;

Message& Message::set(const char *field, void *data) {
    map[field] = data;
    return *this;
}

void* Message::get(const char *field) const { return (void*) const_cast<Message*>(this)->map[field]; }
