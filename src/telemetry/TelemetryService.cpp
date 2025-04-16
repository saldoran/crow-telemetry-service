#include "telemetry/TelemetryService.h"
#include <numeric>

namespace telemetry {

TelemetryService::TelemetryService(const std::shared_ptr<TelemetryStorage> &storage)
    : m_storage(storage)
{
}

void TelemetryService::saveEvent(const std::string& eventName, const TelemetryEvent& event)
{
    m_storage->addEvent(eventName, event);
}

std::optional<double> TelemetryService::calculateMean(const std::string& eventName, std::optional<std::int64_t> start,
                                         std::optional<std::int64_t> end,
                                         const std::string& unit) 
 {
    auto events = m_storage->getEvents(eventName, start, end);
    if (events.empty()) return std::nullopt;
    
    double total = 0.0;
    size_t count = 0;
    for (const auto& ev : events) {
        if (ev.values.empty()) continue;
        double sum = std::accumulate(ev.values.begin(), ev.values.end(), 0.0);
        total += sum / ev.values.size();
        ++count;
    }
    double mean = (count > 0) ? (total / count) : 0.0;
    if (unit == "milliseconds")
        mean *= 1000;
    return mean;
}

} // namespace telemetry
