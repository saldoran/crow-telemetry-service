#include <gtest/gtest.h>
#include <memory>
#include "telemetry/TelemetryService.h"
#include "telemetry/TelemetryStorage.h"

using namespace telemetry;

TEST(TelemetryServiceTest, NoData)
{
  auto storage = std::make_shared<TelemetryStorage>();
  TelemetryService svc(storage);
  auto m = svc.calculateMean("none");
  EXPECT_FALSE(m.has_value());
}

TEST(TelemetryServiceTest, SingleEvent)
{
  auto storage = std::make_shared<TelemetryStorage>();
  TelemetryService svc(storage);

  storage->addEvent("e", TelemetryEvent{{5.0, 15.0}, 0});
  auto m = svc.calculateMean("e");
  ASSERT_TRUE(m.has_value());
  EXPECT_DOUBLE_EQ(*m, 10.0);
}

TEST(TelemetryServiceTest, MultipleAndUnit)
{
  auto storage = std::make_shared<TelemetryStorage>();
  TelemetryService svc(storage);

  storage->addEvent("e", TelemetryEvent{{1.0}, 0});
  storage->addEvent("e", TelemetryEvent{{2.0}, 0});
  auto m1 = svc.calculateMean("e", std::nullopt, std::nullopt, "seconds");
  EXPECT_DOUBLE_EQ(*m1, 1.5);

  auto m2 = svc.calculateMean("e", std::nullopt, std::nullopt, "milliseconds");
  EXPECT_DOUBLE_EQ(*m2, 1500.0);
}