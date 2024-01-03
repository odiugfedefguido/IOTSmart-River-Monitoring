#include "StateMachine.h"
#include "Arduino.h"

#include "../serial/MsgService.h"

static SystemState currentState = AUTOMATIC;

SystemState StateMachine::getCurrentState() {
  return currentState;
}

String getStatusText() {
  switch (currentState) {
    case AUTOMATIC:
      return "AUTOMATIC";
      break;
    case MANUAL:
      return "MANUAL";
      break;
  }
}

void StateMachine::transitionTo(SystemState nextState) {
  currentState = nextState;
  MsgService.sendMsg("STATUS;" + getStatusText());
}
