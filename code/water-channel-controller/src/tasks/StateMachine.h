#pragma once

// Definizione dell'enumerazione per lo stato del sistema
enum SystemState {
    AUTOMATIC_STATE,  // Stato automatico
    MANUAL_STATE,     // Stato manuale
    DASHBOARD_STATE  // Stato dashboard
};

// Spazio dei nomi per la macchina a stati
namespace StateMachine {
    // Funzione per transizionare verso il prossimo stato del sistema
    void transitionTo(SystemState nextState);

    // Funzione per ottenere lo stato attuale del sistema
    SystemState getCurrentState();
};
