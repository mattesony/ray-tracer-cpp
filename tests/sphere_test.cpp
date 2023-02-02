#include "../src/sphere.h"

#include "../src/ray.h"
#include "../src/transformations.h"
#include "./testing_tools.h"
#include "gmock/gmock.h"

using Eigen::Vector4f;

TEST(SphereTest, IntersectTwice) {
  /*
  Scenario: A ray intersects a sphere at two points
  */
  Ray r = Ray(point(0, 0, -5), vector(0, 0, 1));
  Sphere s = Sphere();
  std::vector<float> xs = s.intersects(r);
  EXPECT_EQ(xs.size(), 2);
  EXPECT_EQ(xs[0], 4.0);
  EXPECT_EQ(xs[1], 6.0);
}

TEST(SphereTest, IntersectTangent) {
  /*
  Scenario: A ray intersects a sphere at a tangent
  */
  Ray r = Ray(point(0, 1, -5), vector(0, 0, 1));
  Sphere s = Sphere();
  std::vector<float> xs = s.intersects(r);
  EXPECT_EQ(xs.size(), 2);
  EXPECT_EQ(xs[0], 5.0);
  EXPECT_EQ(xs[1], 5.0);
}

TEST(SphereTest, NoIntersect) {
  /*
  Scenario: A ray misses a sphere
  */
  Ray r = Ray(point(0, 2, -5), vector(0, 0, 1));
  Sphere s = Sphere();
  std::vector<float> xs = s.intersects(r);
  EXPECT_EQ(xs.size(), 0);
}

TEST(SphereTest, IntersectRayInside) {
  /*
  Scenario: A ray originates inside a sphere
  */
  Ray r = Ray(point(0, 0, 0), vector(0, 0, 1));
  Sphere s = Sphere();
  std::vector<float> xs = s.intersects(r);
  EXPECT_EQ(xs.size(), 2);
  EXPECT_EQ(xs[0], -1.0);
  EXPECT_EQ(xs[1], 1.0);
}

TEST(SphereTest, SphereBehindRay) {
  /*
  Scenario: A sphere is behind a ray
  */
  Ray r = Ray(point(0, 0, 5), vector(0, 0, 1));
  Sphere s = Sphere();
  std::vector<float> xs = s.intersects(r);
  EXPECT_EQ(xs.size(), 2);
  EXPECT_EQ(xs[0], -6.0);
  EXPECT_EQ(xs[1], -4.0);
}

TEST(SphereTest, SphereDefaultTransform) {
  /*
  Scenario: A sphere's default transformation
  */
  Sphere s = Sphere();
  EXPECT_EQ(s.transform, Matrix4f::Identity());
}

TEST(SphereTest, SphereChangeTransform) {
  /*
  Scenario: Changing a sphere's transformation
  */
  Sphere s = Sphere();
  Matrix4f t = translation(2, 3, 4);
  s.set_transform(t);
  EXPECT_EQ(s.transform, t);
}

TEST(SphereTest, IntersectTranslatedSphere) {
  /*
  Scenario: Intersecting a translated sphere with a ray
  */
  Ray r = Ray(point(0, 0, -5), vector(0, 0, 1));
  Sphere s = Sphere();
  s.set_transform(translation(5, 0, 0));
  std::vector<float> xs = s.intersects(r);
  EXPECT_EQ(xs.size(), 0);
}
