// StateMachine.h
#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include "SystemState.h"

class StateMachine {
public:
    static SystemState getCurrentState();
    static void transitionTo(SystemState newState);
    // Altri metodi per gestire la transizione degli stati, se necessario

private:
    static SystemState currentState;
};

#endif  // STATE_MACHINE_H
