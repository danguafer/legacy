#pragma once

#include "StateMachine.h"

namespace Silexars {
    namespace etc {
        class StateMachine::State {
            public:
                virtual ~State();
                virtual void run() = 0;

                StateMachine* getStateMachine();
            private:
                friend class StateMachine;
                StateMachine* stateMachine;
        };
    }
}
