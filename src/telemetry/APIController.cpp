#include "telemetry/APIController.h"

namespace telemetry
{
  APIController::APIController(crow::SimpleApp &app, TelemetryService &service)
    : m_app(app)
    , m_service(service)
  {
  }

  void APIController::setupRoutes()
  {
    // Route for saving event via POST /paths/<event>
    CROW_ROUTE(m_app, "/paths/<string>")
    .methods("POST"_method)
    ([this](const crow::request &req, const std::string &eventName)  -> crow::response
    {
      auto body = crow::json::load(req.body);
      if (!body || !body.has("values") || !body.has("date"))
      {
        return crow::response(400, R"({"error":"Invalid JSON"})");
      }
      
      telemetry::TelemetryEvent ev;
      for (const auto &v : body["values"])
      {
        ev.values.push_back(v.d());
      }
      ev.timestamp = body["date"].i();
      
      m_service.saveEvent(eventName, ev);
      
      return crow::response(201);
    });

    // Route for retrieving mean value via GET /paths/<event>/meanLength
    CROW_ROUTE(m_app, "/paths/<string>/meanLength")
      .methods("GET"_method)
    ([this](const crow::request &req, const std::string &eventName) -> crow::response
    {
      auto body = crow::json::load(req.body);
      std::string unit = "seconds";
      std::optional<std::int64_t> start;
      std::optional<std::int64_t> end;
      if (body)
      {
        if (body.has("resultUnit"))
          unit = body["resultUnit"].s();
        if (body.has("startTimestamp"))
          start = body["startTimestamp"].i();
        if (body.has("endTimestamp"))
          end = body["endTimestamp"].i();
      }
      auto optMean = m_service.calculateMean(eventName, start, end, unit);
      if (!optMean)
          return crow::response(404, "{\"error\":\"no data\"}");

      crow::json::wvalue res_json;
      res_json["mean"] = *optMean;

      auto s = res_json.dump();
      return crow::response{200, s};
    });
  }
}
