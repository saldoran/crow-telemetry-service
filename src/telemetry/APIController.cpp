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
    ([this](const crow::request &req, crow::response &res, const std::string &eventName)
    {
      auto body = crow::json::load(req.body);
      if (!body || !body.has("values") || !body.has("date"))
      {
        res.code = 400;
        res.write("Invalid JSON");
        res.end();
        return;
      }
      
      telemetry::TelemetryEvent ev;
      for (const auto &v : body["values"])
      {
        ev.values.push_back(v.d());
      }
      ev.timestamp = body["date"].i();
      
      m_service.saveEvent(eventName, ev);
      
      res.code = 200;
      res.end();
    });

    // Route for retrieving mean value via GET /paths/<event>/meanLength
    CROW_ROUTE(m_app, "/paths/<string>/meanLength")
      .methods("GET"_method)
    ([this](const crow::request &req, crow::response &res, const std::string &eventName)
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
      double mean = m_service.calculateMean(eventName, start, end, unit);
      
      crow::json::wvalue res_json;
      res_json["mean"] = mean;
      
      res.code = 200;
      res.write(res_json.dump());
      res.end();
    });
  }
}