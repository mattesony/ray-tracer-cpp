#include "../src/ray.h"

#include "../src/transformations.h"
#include "./testing_tools.h"
#include "gmock/gmock.h"

using Eigen::Vector4f;

TEST(RayTest, CreateQuery) {
  /*
  Scenario: Creating and querying a ray
  */
  Vector4f origin = point(1, 2, 3);
  Vector4f direction = vector(4, 5, 6);
  auto r = Ray(origin, direction);
  EXPECT_EQ(r.origin, origin);
  EXPECT_EQ(r.direction, direction);
}

TEST(RayTest, PointDistance) {
  /*
  Scenario: Computing a point from a distance
  */
  auto r = Ray(point(2, 3, 4), vector(1, 0, 0));
  EXPECT_EQ(r.position(0), point(2, 3, 4));
  EXPECT_EQ(r.position(1), point(3, 3, 4));
  EXPECT_EQ(r.position(-1), point(1, 3, 4));
  EXPECT_EQ(r.position(2.5), point(4.5, 3, 4));
}

TEST(RayTest, Translate) {
  /*
  Scenario: Translating a ray
  */
  auto r = Ray(point(1, 2, 3), vector(0, 1, 0));
  Matrix4f m = translation(3, 4, 5);
  auto r2 = r.transform(m);
  EXPECT_EQ(r2.origin, point(4, 6, 8));
  EXPECT_EQ(r2.direction, vector(0, 1, 0));
}

TEST(RayTest, Scale) {
  /*
  Scenario: Scaling a ray
  */
  auto r = Ray(point(1, 2, 3), vector(0, 1, 0));
  Matrix4f m = scaling(2, 3, 4);
  auto r2 = r.transform(m);
  EXPECT_EQ(r2.origin, point(2, 6, 12));
  EXPECT_EQ(r2.direction, vector(0, 3, 0));
}
