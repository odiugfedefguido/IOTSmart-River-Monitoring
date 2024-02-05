package http;

import data.ControlState;
import data.DataStore;
import io.vertx.core.AbstractVerticle;
import io.vertx.core.http.HttpServerResponse;
import io.vertx.core.json.JsonObject;
import io.vertx.ext.web.Router;
import io.vertx.ext.web.RoutingContext;
import io.vertx.ext.web.handler.BodyHandler;
import io.vertx.ext.web.handler.CorsHandler;

/**
 * Server for JSON data of the River Monitoring System.
 */
public class HTTPServer extends AbstractVerticle {

    private int port;
    private DataStore dataStore = DataStore.getInstance();

    public HTTPServer(int port) {
        this.port = port;
    }

    @Override
    public void start() {
        Router router = Router.router(vertx);
        router.route().handler(CorsHandler.create(".*."));
        router.route().handler(BodyHandler.create());

        // updating the valve angle
        router.post("/api/data").handler(this::handleAddNewData);

        // switching between AUTOMATIC and DASHBOARD mode
        router.post("/api/mode").handler(this::handleToggleDashboardMode);

        // fetching JSON data
        router.get("/api/data").handler(this::handleGetData);

        vertx
                .createHttpServer()
                .requestHandler(router)
                .listen(port);

        log("HTTP service ready on port: " + port);
    }

    // POST: /api/data
    private void handleAddNewData(RoutingContext routingContext) {
        HttpServerResponse response = routingContext.response();
        log("Received new message – " + routingContext.getBodyAsString());

        if (dataStore.getControlState().equals(ControlState.DASHBOARD)) {
            JsonObject res = routingContext.getBodyAsJson();
            if (res == null) {
                sendError(400, response);
            } else {
                float value = res.getInteger("valveAngle");
                dataStore.setValveAngle((int) value);
                response.setStatusCode(200).end();
            }
        }
    }

    // POST: /api/mode
    private void handleToggleDashboardMode(RoutingContext routingContext) {
        HttpServerResponse response = routingContext.response();
        log("Received new message – " + routingContext.getBodyAsString());

        if (dataStore.getControlState().equals(ControlState.AUTOMATIC)) {
            log("Switching to dashboard control mode.");
            dataStore.setControlState(ControlState.DASHBOARD);
            response.setStatusCode(200).end();
        } else if (dataStore.getControlState().equals(ControlState.DASHBOARD)) {
            log("Switching to automatic control mode.");
            dataStore.setControlState(ControlState.AUTOMATIC);
            response.setStatusCode(200).end();
        }
    }

    // GET: /api/data
    private void handleGetData(RoutingContext routingContext) {
        var data = dataStore.getJSON();

        routingContext.response()
                .putHeader("content-type", "application/json")
                .end(data.encodePrettily());
    }

    private void sendError(int statusCode, HttpServerResponse response) {
        response.setStatusCode(statusCode).end();
    }

    private void log(String msg) {
        System.out.println("[DATA SERVICE] " + msg);
    }

}
