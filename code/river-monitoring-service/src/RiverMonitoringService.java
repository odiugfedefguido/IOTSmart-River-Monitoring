import http.HTTPServer;
import io.vertx.core.AbstractVerticle;
import io.vertx.core.Vertx;
import mqtt.MQTTAgent;

public class RiverMonitoringService extends AbstractVerticle {
    public static void main(String[] args) throws Exception {
        Vertx vertx = Vertx.vertx();

        // MQTT part
        MQTTAgent mqttAgent = new MQTTAgent();
        vertx.deployVerticle(mqttAgent);

        // HTTP part
        HTTPServer httpServer = new HTTPServer(8080);
        vertx.deployVerticle(httpServer);
    }
}
