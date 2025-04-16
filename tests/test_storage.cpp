#include <gtest/gtest.h>
#include "telemetry/TelemetryStorage.h"

using namespace telemetry;

TEST(TelemetryStorageTest, AddAndRetrieve)
{
  TelemetryStorage st;
  TelemetryEvent ev1{{1.0, 2.0, 3.0}, 100};
  st.addEvent("evt", ev1);

  auto all = st.getEvents("evt");
  ASSERT_EQ(all.size(), 1u);
  EXPECT_EQ(all[0].timestamp, 100);
  EXPECT_EQ(all[0].values, (std::vector<double>{1.0,2.0,3.0}));
}

TEST(TelemetryStorageTest, Filtering)
{
  TelemetryStorage st;
  st.addEvent("evt", TelemetryEvent{{1.0},  50});
  st.addEvent("evt", TelemetryEvent{{2.0}, 150});
  st.addEvent("evt", TelemetryEvent{{3.0}, 250});

  auto f1 = st.getEvents("evt", 100, std::nullopt);
  ASSERT_EQ(f1.size(), 2u);
  EXPECT_EQ(f1[0].timestamp, 150);
  EXPECT_EQ(f1[1].timestamp, 250);

  auto f2 = st.getEvents("evt", std::nullopt, 100);
  ASSERT_EQ(f2.size(), 1u);
  EXPECT_EQ(f2[0].timestamp, 50);
}