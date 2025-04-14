#pragma once

#include <vector>
#include <cstdint>

namespace telemetry {

struct TelemetryEvent {
    std::vector<double> values;  // Data set (f.e., temporary values)
    std::int64_t timestamp;      // time stamp (UNIX-time)
};

} // namespace telemetry