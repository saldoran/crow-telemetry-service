#pragma once

#include "crow_all.h"
#include "TelemetryService.h"

namespace telemetry {

class APIController {
public:
    APIController(crow::SimpleApp& app, TelemetryService& service);
    void setupRoutes();

private:
    crow::SimpleApp& m_app;
    TelemetryService& m_service;
};

} // namespace telemetry
