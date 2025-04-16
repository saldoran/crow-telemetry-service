#pragma once

#include "TelemetryStorage.h"
#include <string>
#include <optional>

namespace telemetry {

class TelemetryService {
public:
    TelemetryService(const std::shared_ptr<TelemetryStorage> &storage);

    // Calls by controller to save an event
    void saveEvent(const std::string& eventName, const TelemetryEvent& event);

    // Calculates average value by saved events
    std::optional<double> calculateMean(const std::string& eventName,
                         std::optional<std::int64_t> start = std::nullopt,
                         std::optional<std::int64_t> end = std::nullopt,
                         const std::string& unit = "seconds");

private:
    std::shared_ptr<TelemetryStorage> m_storage;
};

} // namespace telemetry
