// StateMachine.cpp
#include "StateMachine.h"

SystemState StateMachine::currentState = SystemState::AUTOMATIC_STATE;  // Imposta lo stato iniziale, ad esempio, Automatico

SystemState StateMachine::getCurrentState() {
    return currentState;
}

void StateMachine::transitionTo(SystemState newState) {
    // Implementa la logica per gestire la transizione degli stati
    // Può includere la verifica di condizioni, l'esecuzione di azioni specifiche, ecc.
    currentState = newState;
}
