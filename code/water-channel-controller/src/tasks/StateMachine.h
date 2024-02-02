#pragma once

enum SystemState {
    AUTOMATIC_STATE,
    MANUAL_STATE,
    DASHBOARD_STATE
};

namespace StateMachine {
  void transitionTo(SystemState nextState);
  SystemState getCurrentState();
};