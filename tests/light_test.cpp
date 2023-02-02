#include "../src/light.h"

#include "../src/tuple.h"
#include "./testing_tools.h"
#include "gmock/gmock.h"

using ::testing::FloatEq;

TEST(MaterialTest, Default) {
  /*
  Scenario: The default material
  */
  auto intensity = Vector3f(1, 1, 1);
  auto position = point(0, 0, 0);
  auto light = Light(position, intensity);
  EXPECT_EQ(light.position, position);
  EXPECT_EQ(light.intensity, intensity);
}
