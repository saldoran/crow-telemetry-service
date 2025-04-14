#include "telemetry/TelemetryStorage.h"
namespace telemetry {

void TelemetryStorage::addEvent(const std::string& eventName, const TelemetryEvent& event) {
    std::unique_lock lock(m_mutex);
    // Convert string_view to std::string as key in map
    m_storage[std::string(eventName)].push_back(event);
}

std::vector<TelemetryEvent> TelemetryStorage::getEvents(const std::string& eventName, std::optional<std::int64_t> start,
                                                         std::optional<std::int64_t> end)
{
    std::shared_lock lock(m_mutex);
    auto it = m_storage.find(std::string(eventName));
    if (it == m_storage.end())
        return {};

    const auto &events = it->second;
    if (!start && !end)
        return events; // return copy of entire container

    std::vector<TelemetryEvent> filtered;
    for (const auto &ev : events)
    {
        if (start && ev.timestamp < *start)
            continue;
        if (end && ev.timestamp > *end)
            continue;
        filtered.push_back(ev);
    }
    return filtered; //rvo
}

} // namespace telemetry
