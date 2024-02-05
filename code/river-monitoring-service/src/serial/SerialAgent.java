package serial;

import data.ControlState;
import data.DataStore;

import java.util.Objects;

/**
 * A thread that enables Serial communication on the specified port.
 */
public class SerialAgent extends Thread {
    private final String port;

    /**
     * Create a new SerialAgent.
     *
     * @param port the serial port that the Arduino is connected to
     */
    public SerialAgent(String port) {
        Objects.requireNonNull(port);
        this.port = port;
    }

    public void start() {
        try {
            // create a new serial communication channel
            SerialCommChannel channel = new SerialCommChannel(port, 9600);

            // wait for the Arduino to reboot after establishing the connection
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

                // check for messages to send to the dashboard
                if (dataStore.clearDashboardModeSwitches()) {
                    channel.sendMsg("DASHBOARD");
                }

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
