#include "third_party/crow_all.h"
#include "telemetry/TelemetryService.h"
#include "telemetry/APIController.h"

int main() {
    crow::SimpleApp app;

    auto storage = std::make_shared<telemetry::TelemetryStorage>();
    telemetry::TelemetryService service(storage);
    telemetry::APIController controller(app, service);
    controller.setupRoutes();

    app.port(18080).multithreaded().run();
    return 0;
}
