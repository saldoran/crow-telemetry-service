#pragma once

#include "TelemetryEvent.h"
#include <string>
#include <vector>
#include <optional>
#include <shared_mutex>
#include <unordered_map>

namespace telemetry {

class TelemetryStorage {
public:
    // saves event with name provided
    void addEvent(const std::string& eventName, const TelemetryEvent& event);

    // gets events list by name with optional filtering
    std::vector<TelemetryEvent> getEvents(const std::string& eventName,
                                          std::optional<std::int64_t> start = std::nullopt,
                                          std::optional<std::int64_t> end = std::nullopt);

private:
    std::unordered_map<std::string, std::vector<TelemetryEvent>> m_storage;
    mutable std::shared_mutex m_mutex;
};

} // namespace telemetry
