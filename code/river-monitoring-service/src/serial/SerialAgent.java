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
            // SerialCommChannel channel = new SerialCommChannel("/dev/cu.usbmodem1411",9600);
            /* attesa necessaria per fare in modo che Arduino completi il reboot */
            System.out.println("[SERIAL] Waiting for Arduino rebooting …");
            Thread.sleep(4000);
            System.out.println("[SERIAL] Ready.");

            DataStore dataStore = DataStore.getInstance();

            while (true) {
                String msg = channel.receiveMsg();

                if (msg != null) {
                    // TODO: Remove
                    // System.err.println(msg);
                    if (msg.startsWith("ANGLE")) {
                        int angle = Integer.parseInt(msg.substring(6));
                        if (dataStore.getControlState().equals(ControlState.MANUAL)) {
                            System.out.println("New valve angle from potentiometer: " + angle);
                            dataStore.setValveAngle(angle);
                        }
                    } else if (msg.equals("AUTOMATIC")) {
                        System.out.println("Switching to automatic mode.");
                        dataStore.setControlState(ControlState.AUTOMATIC);
                    } else if (msg.equals("MANUAL")) {
                        System.out.println("Switching to manual mode.");
                        dataStore.setControlState(ControlState.MANUAL);
                    }
                }

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
