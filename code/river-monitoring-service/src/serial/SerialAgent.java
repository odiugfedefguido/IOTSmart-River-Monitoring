package serial;

import data.ControlState;
import data.DataStore;

import java.util.Objects;

public class SerialAgent extends Thread {
    private final String port;

    public SerialAgent(String port) {
        Objects.requireNonNull(port);
        this.port = port;
    }

    public void start() {
        try {
            SerialCommChannel channel = new SerialCommChannel(port, 9600);

            /* attesa necessaria per fare in modo che Arduino completi il reboot */
            System.out.println("[SERIAL] Waiting for Arduino rebooting …");
            Thread.sleep(4000);
            System.out.println("[SERIAL] Ready.");

            DataStore dataStore = DataStore.getInstance();

            while (true) {
                String msg = channel.receiveMsg();
                if (msg != null) {
                    // there is a message on the serial channel

                    if (msg.startsWith("ANGLE")) {
                        // a new valve angle was sent by the potentiometer in manual mode
                        if (dataStore.getControlState().equals(ControlState.MANUAL)) {
                            int angle = Integer.parseInt(msg.substring(6));
                            dataStore.setValveAngle(angle);
                            // System.out.println("New valve angle from potentiometer: " + angle);
                        }
                    } else if (msg.equals("AUTOMATIC") && dataStore.getControlState().equals(ControlState.MANUAL)) {
                        // the system switches back to automatic mode due to button press
                        System.out.println("Switching to automatic mode.");
                        dataStore.setControlState(ControlState.AUTOMATIC);
                    } else if (msg.equals("MANUAL") && dataStore.getControlState().equals(ControlState.AUTOMATIC)) {
                        // the system switches to manual mode due to button press
                        System.out.println("Switching to manual mode.");
                        dataStore.setControlState(ControlState.MANUAL);
                    }
                }

                // check for instructions from the dashboard

                // the valve angle is sent as a command to the Arduino which instructs the servo motor
                channel.sendMsg("NEWANGLE " + dataStore.getValveAngle());
                Thread.sleep(50);
            }
        } catch (InterruptedException e) {
            System.err.println("[SERIAL] Caught interrupt. Terminating serial agent.");
        } catch (Exception e) {
            System.err.println("[SERIAL] Caught exception. Terminating serial agent.");
            e.printStackTrace();
        }
    }
}
