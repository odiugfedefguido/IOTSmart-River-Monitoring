#include "StateMachine.h"
#include "Arduino.h"

// Define the initial system state
static SystemState currentState = AUTOMATIC_STATE;

// Method to get the current system state
SystemState StateMachine::getCurrentState() {
  return currentState; // Return the current state
}

// Method to transition to a new system state
void StateMachine::transitionTo(SystemState nextState) {
  currentState = nextState; // Update the current state to the next state
}
