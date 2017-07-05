#include "StateMachine.h"
#include "StateMachine.State.h"

using namespace Silexars::etc;

StateMachine::StateMachine(State *state) { setState(state); }

void StateMachine::setState(State *state) {
    state->stateMachine = this;
    this->state = state;
}

StateMachine::State* StateMachine::getState() { return state; }
void StateMachine::run() { state->run(); }
