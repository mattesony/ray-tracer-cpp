#include "../src/world.h"
#include "./testing_tools.h"
#include "gmock/gmock.h"


TEST(WorldTest, Create) {
  /*
  Scenario: Creating a world
  */
  auto w = World();
  EXPECT_EQ(w.objects.size(), 0);
  EXPECT_EQ(w.lights.size(), 0);
}
