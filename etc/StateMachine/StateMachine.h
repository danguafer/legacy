#pragma once

namespace Silexars {
    namespace etc {
        class StateMachine {
            public:
                class State;

                StateMachine(State *state);

                void run();

                void setState(State *state);
                State* getState();
            private:
                State* state;
        };
    }
}

#include "StateMachine.State.h"
