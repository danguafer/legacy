#include "StateMachine.State.h"

using namespace Silexars::etc;

StateMachine::State::~State() {}
StateMachine* StateMachine::State::getStateMachine() { return stateMachine; }
