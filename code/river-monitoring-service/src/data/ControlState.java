package data;

/**
 * Possible states of the internal FSM.
 */
public enum ControlState {
    /**
     * AUTOMATIC mode: The valve opening angle is determined by the 
     * River Monitoring Service based on the distance measurements.
     */
    AUTOMATIC,

    /**
     * MANUAL mode: The valve opening angle is determined by the 
     * potentiometer readings.
     */
    MANUAL,

    /**
     * DASHBOARD mode: The valve opening angle is determined by the 
     * slider control on the dashboard page.
     */
    DASHBOARD
}
