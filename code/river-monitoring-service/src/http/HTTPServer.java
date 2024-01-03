package http;

import data.DataStore;
import io.vertx.core.AbstractVerticle;
import io.vertx.core.http.HttpServerResponse;
import io.vertx.core.json.JsonObject;
import io.vertx.ext.web.Router;
import io.vertx.ext.web.RoutingContext;
import io.vertx.ext.web.handler.BodyHandler;
import io.vertx.ext.web.handler.CorsHandler;

import java.util.LinkedList;

public class HTTPServer extends AbstractVerticle {

    private int port;
    private static final int MAX_SIZE = 10;
    private LinkedList<DataPoint> values;

    public HTTPServer(int port) {
        values = new LinkedList<>();
        this.port = port;
    }

    @Override
    public void start() {
        Router router = Router.router(vertx);
        router.route().handler(CorsHandler.create(".*."));
        router.route().handler(BodyHandler.create());
        router.post("/api/data").handler(this::handleAddNewData);
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
        log("new msg " + routingContext.getBodyAsString());
        JsonObject res = routingContext.getBodyAsJson();
        if (res == null) {
            sendError(400, response);
        } else {
            float value = res.getInteger("valveAngle");
            DataStore.getInstance().setValveAngle((int) value);
            response.setStatusCode(200).end();
        }
    }

    // GET: /api/data
    private void handleGetData(RoutingContext routingContext) {
        var data = DataStore.getInstance().getJSON();

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
