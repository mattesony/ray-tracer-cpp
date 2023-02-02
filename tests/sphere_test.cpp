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

TEST(SphereTest, SphereNormalXAxis) {
  /*
  Scenario: The normal on a sphere at a point on the x axis
  */
  Sphere s = Sphere();
  Vector4f n = s.normal_at(point(1, 0, 0));
  EXPECT_EQ(n, vector(1, 0, 0));
}

TEST(SphereTest, SphereNormalYAxis) {
  /*
  Scenario: The normal on a sphere at a point on the y axis
  */
  Sphere s = Sphere();
  Vector4f n = s.normal_at(point(0, 1, 0));
  EXPECT_EQ(n, vector(0, 1, 0));
}

TEST(SphereTest, SphereNormalZAxis) {
  /*
  Scenario: The normal on a sphere at a point on the z axis
  */
  Sphere s = Sphere();
  Vector4f n = s.normal_at(point(0, 0, 1));
  EXPECT_EQ(n, vector(0, 0, 1));
}

TEST(SphereTest, SphereNormalNonaxial) {
  /*
  Scenario: The normal on a sphere at a nonaxial point
  */
  Sphere s = Sphere();
  Vector4f n = s.normal_at(point(sqrt(3) / 3, sqrt(3) / 3, sqrt(3) / 3));
  compareVectors(n, vector(sqrt(3) / 3, sqrt(3) / 3, sqrt(3) / 3));
}

TEST(SphereTest, NormalizedNormal) {
  /*
  Scenario: The normal is a normalized vector
  */
  Sphere s = Sphere();
  Vector4f n = s.normal_at(point(sqrt(3) / 3, sqrt(3) / 3, sqrt(3) / 3));
  compareVectors(n, vector(sqrt(3) / 3, sqrt(3) / 3, sqrt(3) / 3));
}

TEST(SphereTest, TranslateSphereNormal) {
  /*
  Scenario: Computing the normal on a translated sphere
  */
  Sphere s = Sphere();
  s.set_transform(translation(0, 1, 0));
  Vector4f n = s.normal_at(point(0, 1.70711, -0.70711));
  compareVectors(n, vector(0, 0.70711, -0.70711));
}

TEST(SphereTest, TransformSphereNormal) {
  /*
  Scenario: Computing the normal on a transformed sphere
  */
  Sphere s = Sphere();
  s.set_transform(scaling(1, 0.5, 1) * rotation_z(M_PI / 5));
  Vector4f n = s.normal_at(point(0, sqrt(2) / 2, -sqrt(2) / 2));
  compareVectors(n, vector(0, 0.97014, -0.24254));
}

TEST(SphereTest, DefaultMaterial) {
  /*
  Scenario: A sphere has a default material
  */
  Sphere s = Sphere();
  EXPECT_EQ(s.material, Material());
}
TEST(SphereTest, AssignMaterial) {
  /*
  Scenario: A sphere may be assigned a material
  */
  Sphere s = Sphere();
  Material m = Material();
  m.ambient = 1;
  s.material = m;
  EXPECT_EQ(s.material, m);
  // EXPECT_NE(s.material, Material());
}

/*
Scenario: A sphere has a default material
Given s ← sphere()
When m ← s.material
Then m = material()
Scenario: A sphere may be assigned a material
Given s ← sphere()
And m ← material()
And m.ambient ← 1
When s.material ← m
Then s.material = m
*/
