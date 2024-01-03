package data;

import io.vertx.core.json.JsonArray;
import io.vertx.core.json.JsonObject;

import java.util.Deque;
import java.util.LinkedList;
import java.util.Random;

public class DataStore {
    // the singleton instance
    private static DataStore instance = null;

    // protects against coinciding accesses
    private static final Object lock = new Object();

    // how many items are preserved in the history
    private final int MAX_HISTORY_CAPACITY = 100;

    // the data to be stored
    private ControlState controlState = ControlState.MANUAL;
    private ValveState valveState = ValveState.NORMAL;
    private int valveAngle = 120;
    private Deque<Double> history = new LinkedList<>();

    private final Random random = new Random();

    private DataStore() {
        // Singleton.

        // FIXME: Remove as soon as there is actual data.
        for (int i = 0; i < MAX_HISTORY_CAPACITY; i++) {
            addDataPoint(random.nextDouble(100));
        }
    }

    public static DataStore getInstance() {
        if (instance == null) {
            instance = new DataStore();
        }
        return instance;
    }

    public void addDataPoint(Double datapoint) {
        synchronized (lock) {
            history.addLast(datapoint);

            if (history.size() > MAX_HISTORY_CAPACITY) {
                history.removeFirst();
            }
        }
    }

    public void setControlState(ControlState controlState) {
        synchronized (lock) {
            this.controlState = controlState;
        }
    }

    public void setValveState(ValveState valveState) {
        synchronized (lock) {
            this.valveState = valveState;
        }
    }

    public void setValveAngle(int valveAngle) {
        synchronized (lock) {
            this.valveAngle = valveAngle;
        }
    }

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

            addDataPoint(random.nextDouble(100));
            return data;
        }
    }
}
