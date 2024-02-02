#include "StateMachine.h"
#include "Arduino.h"

static SystemState currentState = AUTOMATIC_STATE;

SystemState StateMachine::getCurrentState() {
  return currentState;
}

void StateMachine::transitionTo(SystemState nextState) {
  currentState = nextState;
}