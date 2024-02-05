package data;

/**
 * States of the system according to distance measurements.
 */
public enum ValveState {
    NORMAL,
    ALARM_TOO_LOW,
    PRE_ALARM_TOO_HIGH,
    ALARM_TOO_HIGH,
    ALARM_TOO_HIGH_CRITIC
}
