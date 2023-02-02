#include "../src/intersection.h"
#include "../src/sphere.h"
#include "./testing_tools.h"
#include "gmock/gmock.h"

using Eigen::Vector4f;

TEST(IntersectionsTest, IntersectionObject) {
  /*
  Scenario: An intersection encapsulates t and object
  */
  auto const s = std::make_shared<Sphere>();
  Intersection i = Intersection(3.5, s);
  EXPECT_EQ(i.t, 3.5);
  EXPECT_EQ(i.object, s);
}

TEST(IntersectionsTest, IntersectionsAggregation) {
  /*
  Scenario: Aggregating intersections
  */
  auto const s = std::make_shared<Sphere>();
  Intersection i1 = Intersection(1, s);
  Intersection i2 = Intersection(2, s);
  std::vector<Intersection> xs = intersections(i1, i2);
  EXPECT_EQ(xs.size(), 2);
  EXPECT_EQ(xs[0].t, 1);
  EXPECT_EQ(xs[1].t, 2);
}

TEST(IntersectionsTest, HitAllPositiveT) {
  /*
  Scenario: The hit, when all intersections have positive t
  */
  auto const s = std::make_shared<Sphere>();
  Intersection i1 = Intersection(1, s);
  Intersection i2 = Intersection(2, s);
  std::vector<Intersection> xs = intersections(i2, i1);
  EXPECT_EQ(hit(xs), i1);
}

TEST(IntersectionsTest, HitSomeNegativeT) {
  /*
  Scenario: The hit, when some intersections have negative t
  */
  auto const s = std::make_shared<Sphere>();
  Intersection i1 = Intersection(-1, s);
  Intersection i2 = Intersection(1, s);
  std::vector<Intersection> xs = intersections(i2, i1);
  EXPECT_EQ(hit(xs), i2);
}

TEST(IntersectionsTest, NoHitAllNegativeT) {
  /*
  Scenario: The hit, when all intersections have negative t
  */
  auto const s = std::make_shared<Sphere>();
  Intersection i1 = Intersection(-2, s);
  Intersection i2 = Intersection(-1, s);
  std::vector<Intersection> xs = intersections(i2, i1);
  auto i = hit(xs);
  EXPECT_EQ(i.t, 0.0);
  EXPECT_EQ(i.object, nullptr);
}

TEST(IntersectionsTest, HitLowestNonNegativeT) {
  /*
  Scenario: The hit is always the lowest nonnegative intersection
  */
  auto const s = std::make_shared<Sphere>();
  Intersection i1 = Intersection(5, s);
  Intersection i2 = Intersection(7, s);
  Intersection i3 = Intersection(-3, s);
  Intersection i4 = Intersection(2, s);
  std::vector<Intersection> xs = intersections(i1, i2, i3, i4);
  EXPECT_EQ(hit(xs), i4);
}

/*

Scenario: Aggregating intersections
  Given s ← sphere()
    And i1 ← intersection(1, s)
    And i2 ← intersection(2, s)
  When xs ← intersections(i1, i2)
  Then xs.count = 2
    And xs[0].t = 1
    And xs[1].t = 2

Scenario: Precomputing the state of an intersection
  Given r ← ray(point(0, 0, -5), vector(0, 0, 1))
    And shape ← sphere()
    And i ← intersection(4, shape)
  When comps ← prepare_computations(i, r)
  Then comps.t = i.t
    And comps.object = i.object
    And comps.point = point(0, 0, -1)
    And comps.eyev = vector(0, 0, -1)
    And comps.normalv = vector(0, 0, -1)

Scenario: Precomputing the reflection vector
  Given shape ← plane()
    And r ← ray(point(0, 1, -1), vector(0, -√2/2, √2/2))
    And i ← intersection(√2, shape)
  When comps ← prepare_computations(i, r)
  Then comps.reflectv = vector(0, √2/2, √2/2)

Scenario: The hit, when an intersection occurs on the outside
  Given r ← ray(point(0, 0, -5), vector(0, 0, 1))
    And shape ← sphere()
    And i ← intersection(4, shape)
  When comps ← prepare_computations(i, r)
  Then comps.inside = false

Scenario: The hit, when an intersection occurs on the inside
  Given r ← ray(point(0, 0, 0), vector(0, 0, 1))
    And shape ← sphere()
    And i ← intersection(1, shape)
  When comps ← prepare_computations(i, r)
  Then comps.point = point(0, 0, 1)
    And comps.eyev = vector(0, 0, -1)
    And comps.inside = true
      # normal would have been (0, 0, 1), but is inverted!
    And comps.normalv = vector(0, 0, -1)

Scenario: The hit should offset the point
  Given r ← ray(point(0, 0, -5), vector(0, 0, 1))
    And shape ← sphere() with:
      | transform | translation(0, 0, 1) |
    And i ← intersection(5, shape)
  When comps ← prepare_computations(i, r)
  Then comps.over_point.z < -EPSILON/2
    And comps.point.z > comps.over_point.z

Scenario: The under point is offset below the surface
  Given r ← ray(point(0, 0, -5), vector(0, 0, 1))
    And shape ← glass_sphere() with:
      | transform | translation(0, 0, 1) |
    And i ← intersection(5, shape)
    And xs ← intersections(i)
  When comps ← prepare_computations(i, r, xs)
  Then comps.under_point.z > EPSILON/2
    And comps.point.z < comps.under_point.z
*/
