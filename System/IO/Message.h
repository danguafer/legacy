#pragma once

#include <map>
#include <string>
#include <iostream>
#include <list>

namespace Silexars {
    namespace System {
        namespace IO {
            class Message {
                public:
                    class Listener {
                        public:
                            ~Listener();

                            void on(const char *message, void (*callback)(const Message&), void* CallbackData = 0);
                        private:
                            struct Callback {
                                Callback(void (*f)(const Message& m), void* userData);

                                void operator()(Message& m);

                                void (*f)(const Message& m);
                                void* userData;
                            };

                            typedef std::list<Callback> Callbacks;
                            typedef std::map<std::string, Callbacks* > CallbacksMap;
                            friend class Message;
                            void dispatch(const char *messageName) const;
                            void dispatch(const char *messageName, Message &message) const;

                            CallbacksMap map;
                    };

                    Message& set(const char* field, void *data);
                    void* get(const char* field) const;

                    template <class T>
                    Message& set(const char *field, T data) {
                        union void_T { T t; void* v; };
                        void_T vt; vt.t = data;
                        return set(field, vt.v);
                    }

                    template <class T>
                    T get(const char* field) const {
                        union void_T { T t; void* v; };
                        void_T vt; vt.v = get(field);
                        return vt.t;
                    }

                    template <class T>
                    void dispatch(T* target, const char* name) { set("Target", target); ((Listener*) target)->dispatch(name, *this); set("Target", 0); }

                private:
                    std::map<std::string, void*> map;
            };
        }
    }
}
