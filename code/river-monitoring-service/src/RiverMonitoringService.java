import http.HTTPServer;
import io.vertx.core.AbstractVerticle;
import io.vertx.core.Vertx;
import mqtt.MQTTAgent;
import serial.SerialAgent;
import serial.ShowSerialPorts;

public class RiverMonitoringService extends AbstractVerticle {
    public static void main(String[] args) throws Exception {

        String serialPort;

        if (args.length == 0) {
            System.out.print("No serial port specified. Presuming: " + ShowSerialPorts.getDefault() + "\n");
            ShowSerialPorts.display();
            serialPort = ShowSerialPorts.getDefault();
        } else {
            serialPort = args[0];
        }

        Vertx vertx = Vertx.vertx();

        // MQTT part
        MQTTAgent mqttAgent = new MQTTAgent();
        vertx.deployVerticle(mqttAgent);

        // HTTP part
        HTTPServer httpServer = new HTTPServer(8080);
        vertx.deployVerticle(httpServer);

        // Serial part
        SerialAgent serialAgent = new SerialAgent(serialPort);
        serialAgent.start();
    }
}
