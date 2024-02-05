package serial;

import jssc.SerialPortList;

/**
 * Displays all available serial ports on the system.
 * Based on the class provided in the lecture.
 */
public class ShowSerialPorts {

    /**
     * Print available serial ports to the console.
     */
    public static void display() {
        if (SerialPortList.getPortNames().length > 0) {
            System.out.println("[SERIAL] Available ports:");
            for (String portName : SerialPortList.getPortNames()) {
                System.out.println(portName);
            }
        }
    }

    /**
     * Get the first available serial port.
     *
     * @return the serial port
     * @throws RuntimeException if no serial ports are available
     */
    public static String getDefault() {
        if (SerialPortList.getPortNames().length > 0) {
            return SerialPortList.getPortNames()[0];
        } else {
            throw new RuntimeException("[SERIAL] No serial ports available.");
        }
    }
}

