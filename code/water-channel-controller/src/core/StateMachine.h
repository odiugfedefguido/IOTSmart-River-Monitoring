#pragma once

// State variables
enum SystemState
{
  MANUAL,
  AUTOMATIC
};

namespace StateMachine {
  void transitionTo(SystemState nextState);
  SystemState getCurrentState();
};
