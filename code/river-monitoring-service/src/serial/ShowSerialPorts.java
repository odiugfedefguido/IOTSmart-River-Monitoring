package serial;

import jssc.SerialPortList;

public class ShowSerialPorts {

    public static void display() {
        if (SerialPortList.getPortNames().length > 0) {
            /* detect serial ports */
            System.out.println("[SERIAL] Available ports:");
            for (String portName : SerialPortList.getPortNames()) {
                System.out.println(portName);
            }
        }
    }

    public static String getDefault() {
        if (SerialPortList.getPortNames().length > 0) {
            return SerialPortList.getPortNames()[0];
        } else {
            throw new RuntimeException("[SERIAL] No serial ports available.");
        }
    }

    public static void main(String[] args) {
        display();
    }

}

