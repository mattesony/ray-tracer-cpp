#include "../src/tuple.h"

#include "./testing_tools.h"
#include "gmock/gmock.h"

TEST(TupleTest, Reflect45) {
  /*
  Scenario: Reflecting a vector approaching at 45°
  */
  auto v = vector(1, -1, 0);
  auto n = vector(0, 1, 0);
  auto r = reflect(v, n);
  EXPECT_EQ(r, vector(1, 1, 0));
}

TEST(TupleTest, ReflectSlant) {
  /*
  Scenario: Reflecting a vector off a slanted surface
  */
  auto v = vector(0, -1, 0);
  auto n = vector(sqrt(2) / 2, sqrt(2) / 2, 0);
  auto r = reflect(v, n);
  compareVectors(r, vector(1, 0, 0));
}
