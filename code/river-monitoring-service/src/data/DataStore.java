package data;

import io.vertx.core.json.JsonArray;
import io.vertx.core.json.JsonObject;

import java.util.Deque;
import java.util.LinkedList;
import java.util.Random;

/**
 * Store for the internal state of the River Monitoring Service.
 */
public class DataStore {
    // the singleton instance
    private static DataStore instance = null;

    // protects against coinciding accesses
    private static final Object lock = new Object();

    // the data to be stored
    private ControlState controlState = ControlState.AUTOMATIC;
    private ValveState valveState = ValveState.NORMAL;
    private int valveAngle = 120;

    // a flag indicating that there is a switch to or from dashboard mode
    // that has not yet been sent to the Arduino – a cheap blocking queue
    private boolean hasWaitingDashboardModeSwitch = false;

    // previous datastores
    private final Deque<Double> history = new LinkedList<>();

    private final Random random = new Random();

    private DataStore() {
        // Singleton.
    }

    /**
     * Retrieve the singleton instance of this data store.
     */
    public static DataStore getInstance() {
        if (instance == null) {
            instance = new DataStore();
        }
        return instance;
    }

    /**
     * Add a new data point to the history.
     */
    public void addDataPoint(Double datapoint) {
        synchronized (lock) {
            history.addLast(datapoint);

            // how many items are preserved in the history
            int MAX_HISTORY_CAPACITY = 100;
            if (history.size() > MAX_HISTORY_CAPACITY) {
                history.removeFirst();
            }
        }
    }

    /**
     * Update the current control state (see {@link ControlState}).
     * If the new or current state was the {@link ControlState#DASHBOARD},
     * then the {@link DataStore#hasWaitingDashboardModeSwitch} flag is set to true.
     */
    public void setControlState(ControlState controlState) {
        synchronized (lock) {
            if (controlState.equals(ControlState.DASHBOARD) || this.controlState.equals(ControlState.DASHBOARD)) {
                hasWaitingDashboardModeSwitch = true;
            }

            this.controlState = controlState;
        }
    }

    /**
     * Set the state of the valve to one of {@link ValveState}.
     */
    public void setValveState(ValveState valveState) {
        synchronized (lock) {
            this.valveState = valveState;
        }
    }

    /**
     * Clear the {@link #hasWaitingDashboardModeSwitch} flag.
     *
     * @return true if it was dirty, false otherwise
     */
    public boolean clearDashboardModeSwitches() {
        synchronized (lock) {
            boolean previousValue = hasWaitingDashboardModeSwitch;
            hasWaitingDashboardModeSwitch = false;
            return previousValue;
        }
    }

    public void setValveAngle(int valveAngle) {
        synchronized (lock) {
            this.valveAngle = valveAngle;
        }
    }

    public int getValveAngle() {
        return valveAngle;
    }

    public ControlState getControlState() {
        synchronized (lock) {
            return this.controlState;
        }
    }

    /**
     * Return a JSON representation of the internal state.
     */
    public JsonObject getJSON() {
        synchronized (lock) {
            JsonArray dataPoints = new JsonArray();
            for (Double datapoint : history) {
                dataPoints.add(datapoint);
            }

            JsonObject data = new JsonObject();
            data.put("controlState", controlState.toString());
            data.put("valveState", valveState.toString());
            data.put("valveAngle", valveAngle);
            data.put("history", dataPoints);

            return data;
        }
    }
}
