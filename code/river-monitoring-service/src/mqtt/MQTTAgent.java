package mqtt;

import data.ControlState;
import data.DataStore;
import data.Frequency;
import data.ValveState;
import io.netty.handler.codec.mqtt.MqttQoS;
import io.vertx.core.AbstractVerticle;
import io.vertx.core.buffer.Buffer;
import io.vertx.mqtt.MqttClient;

/*
 * MQTT Agent
 */
public class MQTTAgent extends AbstractVerticle {

    private static final String BROKER_ADDRESS = "broker.mqtt-dashboard.com";
    private static final String WATER_LEVEL_TOPIC = "esiot-2023-smart-river-monitoring-45983";
    private static final String FREQUENCY_TOPIC = "esiot-2023-smart-river-monitoring-58329";

    private MqttClient client;

    private final double WL1 = 50;
    private final double WL2 = 30;
    private final double WL3 = 20;
    private final double WL4 = 10;

    private final int ANGLE_0_PERCENT = 0;
    private final int ANGLE_25_PERCENT = 45;
    private final int ANGLE_50_PERCENT = 90;
    private final int ANGLE_100_PERCENT = 180;


    public MQTTAgent() {
    }

    @Override
    public void start() {
        client = MqttClient.create(vertx);

        client.connect(1883, BROKER_ADDRESS, c -> {

            System.out.println("[MQTT AGENT] connected");
            System.out.println("[MQTT AGENT] subscribing …");

            DataStore dataStore = DataStore.getInstance();

            // event handler for published messages
            client.publishHandler(s -> {
                        double waterLevel = Double.parseDouble(s.payload().toString());
                        dataStore.addDataPoint(waterLevel);

                        if (dataStore.getControlState().equals(ControlState.AUTOMATIC)) {
                            // compute the internal valve state and adjust valve angle
                            // and frequencies acccordingly
                            if (waterLevel > WL1) {
                                dataStore.setValveState(ValveState.ALARM_TOO_LOW);
                                dataStore.setValveAngle(ANGLE_0_PERCENT);
                                sendFrequencyToESP(Frequency.F1);
                            } else if (waterLevel > WL2) {
                                dataStore.setValveState(ValveState.NORMAL);
                                dataStore.setValveAngle(ANGLE_25_PERCENT);
                                sendFrequencyToESP(Frequency.F1);
                            } else if (waterLevel > WL3) {
                                dataStore.setValveState(ValveState.PRE_ALARM_TOO_HIGH);
                                dataStore.setValveAngle(ANGLE_25_PERCENT);
                                sendFrequencyToESP(Frequency.F2);
                            } else if (waterLevel > WL4) {
                                dataStore.setValveState(ValveState.ALARM_TOO_HIGH);
                                dataStore.setValveAngle(ANGLE_50_PERCENT);
                                sendFrequencyToESP(Frequency.F2);
                            } else {
                                dataStore.setValveState(ValveState.ALARM_TOO_HIGH_CRITIC);
                                dataStore.setValveAngle(ANGLE_100_PERCENT);
                                sendFrequencyToESP(Frequency.F2);
                            }
                        }

                    })
                    .subscribe(WATER_LEVEL_TOPIC, MqttQoS.EXACTLY_ONCE.value());
        });
    }

    // send new frequencies to the ESP via MQTT
    private void sendFrequencyToESP(Frequency frequency) {
        client.publish(FREQUENCY_TOPIC,
                Buffer.buffer(frequency.toString()),
                MqttQoS.AT_LEAST_ONCE,
                false,
                false);
    }

}