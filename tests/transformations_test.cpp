#include "../src/transformations.h"

#include <cmath>

#include "../src/tuple.h"
#include "gmock/gmock.h"

using Eigen::Vector4f;

TEST(TransformationsTest, Translate) {
  /*
  Scenario: Multiplying by a translation matrix
  */
  Matrix4f transform = translation(5, -3, 2);
  Vector4f p = point(-3, 4, 5);
  EXPECT_EQ(transform * p, point(2, 1, 7));
}

TEST(TransformationsTest, InverseTranslate) {
  /*
  Scenario: Multiplying by the inverse of a translation matrix
  */
  Matrix4f transform = translation(5, -3, 2);
  Vector4f p = point(-3, 4, 5);
  EXPECT_EQ(transform.inverse() * p, point(-8, 7, 3));
}

TEST(TransformationsTest, VectorTranslateDoesNothing) {
  /*
  Scenario: Translation does not affect vectors
  */
  Matrix4f transform = translation(5, -3, 2);
  Vector4f v = vector(-3, 4, 5);
  EXPECT_EQ(transform * v, v);
}

TEST(TransformationsTest, ScalePoint) {
  /*
  Scenario: A scaling matrix applied to a point
  */
  Matrix4f transform = scaling(2, 3, 4);
  Vector4f p = point(-4, 6, 8);
  EXPECT_EQ(transform * p, point(-8, 18, 32));
}

TEST(TransformationsTest, ScaleVector) {
  /*
  Scenario: A scaling matrix applied to a vector
  */
  Matrix4f transform = scaling(2, 3, 4);
  Vector4f v = vector(-4, 6, 8);
  EXPECT_EQ(transform * v, vector(-8, 18, 32));
}

TEST(TransformationsTest, InverseScale) {
  /*
  Scenario: Multiplying by the inverse of a scaling matrix
  */
  Matrix4f transform = scaling(2, 3, 4);
  Vector4f v = vector(-4, 6, 8);
  EXPECT_EQ(transform.inverse() * v, vector(-2, 2, 2));
}

TEST(TransformationsTest, Reflection) {
  /*
  Scenario: Reflection is scaling by a negative value
  */
  Matrix4f transform = scaling(-1, 1, 1);
  Vector4f p = point(2, 3, 4);
  EXPECT_EQ(transform * p, point(-2, 3, 4));
}

TEST(TransformationsTest, RotateX) {
  /*
  Scenario: Rotating a point around the x axis
  */
  Vector4f p = point(0, 1, 0);
  Matrix4f half_quarter = rotation_x(M_PI / 4);
  Matrix4f full_quarter = rotation_x(M_PI / 2);
  EXPECT_EQ(half_quarter * p, point(0, sqrtf(2) / 2, sqrtf(2) / 2));
  EXPECT_EQ(full_quarter * p, point(0, 0, 1));
}

TEST(TransformationsTest, InverseRotateX) {
  /*
  Scenario: The inverse of an x-rotation rotates in the opposite direction
  */
  Vector4f p = point(0, 1, 0);
  Matrix4f half_quarter = rotation_x(M_PI / 4);
  EXPECT_EQ(half_quarter.inverse() * p, point(0, sqrtf(2) / 2, -sqrtf(2) / 2));
}

TEST(TransformationsTest, RotateY) {
  /*
  Scenario: Rotating a point around the y axis
  */
  Vector4f p = point(0, 0, 1);
  Matrix4f half_quarter = rotation_y(M_PI / 4);
  Matrix4f full_quarter = rotation_y(M_PI / 2);
  EXPECT_EQ(half_quarter * p, point(sqrtf(2) / 2, 0, sqrtf(2) / 2));
  EXPECT_EQ(full_quarter * p, point(1, 0, 0));
}

TEST(TransformationsTest, RotateZ) {
  /*
  Scenario: Rotating a point around the z axis
  */
  Vector4f p = point(0, 1, 0);
  Matrix4f half_quarter = rotation_z(M_PI / 4);
  Matrix4f full_quarter = rotation_z(M_PI / 2);
  EXPECT_EQ(half_quarter * p, point(-sqrtf(2) / 2, sqrtf(2) / 2, 0));
  EXPECT_EQ(full_quarter * p, point(-1, 0, 0));
}

TEST(TransformationsTest, ShearXtoY) {
  /*
  Scenario: A shearing transformation moves x in proportion to y
  */
  Matrix4f transform = shearing(1, 0, 0, 0, 0, 0);
  Vector4f p = point(2, 3, 4);
  EXPECT_EQ(transform * p, point(5, 3, 4));
}

TEST(TransformationsTest, ShearXtoZ) {
  /*
  Scenario: A shearing transformation moves x in proportion to z
  */
  Matrix4f transform = shearing(0, 1, 0, 0, 0, 0);
  Vector4f p = point(2, 3, 4);
  EXPECT_EQ(transform * p, point(6, 3, 4));
}

TEST(TransformationsTest, ShearYtoX) {
  /*
  Scenario: A shearing transformation moves y in proportion to x
  */
  Matrix4f transform = shearing(0, 0, 1, 0, 0, 0);
  Vector4f p = point(2, 3, 4);
  EXPECT_EQ(transform * p, point(2, 5, 4));
}

TEST(TransformationsTest, ShearYtoZ) {
  /*
  Scenario: A shearing transformation moves y in proportion to z
  */
  Matrix4f transform = shearing(0, 0, 0, 1, 0, 0);
  Vector4f p = point(2, 3, 4);
  EXPECT_EQ(transform * p, point(2, 7, 4));
}

TEST(TransformationsTest, ShearZtoX) {
  /*
  Scenario: A shearing transformation moves z in proportion to x
  */
  Matrix4f transform = shearing(0, 0, 0, 0, 1, 0);
  Vector4f p = point(2, 3, 4);
  EXPECT_EQ(transform * p, point(2, 3, 6));
}

TEST(TransformationsTest, ShearZtoY) {
  /*
  Scenario: A shearing transformation moves z in proportion to y
  */
  Matrix4f transform = shearing(0, 0, 0, 0, 0, 1);
  Vector4f p = point(2, 3, 4);
  EXPECT_EQ(transform * p, point(2, 3, 7));
}

/*
Scenario: Individual transformations are applied in sequence
  Given p ← point(1, 0, 1)
    And A ← rotation_x(π / 2)
    And B ← scaling(5, 5, 5)
    And C ← translation(10, 5, 7)
  # apply rotation first
  When p2 ← A * p
  Then p2 = point(1, -1, 0)
  # then apply scaling
  When p3 ← B * p2
  Then p3 = point(5, -5, 0)
  # then apply translation
  When p4 ← C * p3
  Then p4 = point(15, 0, 7)

Scenario: Chained transformations must be applied in reverse order
  Given p ← point(1, 0, 1)
    And A ← rotation_x(π / 2)
    And B ← scaling(5, 5, 5)
    And C ← translation(10, 5, 7)
  When T ← C * B * A
  Then T * p = point(15, 0, 7)

Scenario: The transformation matrix for the default orientation
  Given from ← point(0, 0, 0)
    And to ← point(0, 0, -1)
    And up ← vector(0, 1, 0)
  When t ← view_transform(from, to, up)
  Then t = identity_matrix

Scenario: A view transformation matrix looking in positive z direction
  Given from ← point(0, 0, 0)
    And to ← point(0, 0, 1)
    And up ← vector(0, 1, 0)
  When t ← view_transform(from, to, up)
  Then t = scaling(-1, 1, -1)

Scenario: The view transformation moves the world
  Given from ← point(0, 0, 8)
    And to ← point(0, 0, 0)
    And up ← vector(0, 1, 0)
  When t ← view_transform(from, to, up)
  Then t = translation(0, 0, -8)

Scenario: An arbitrary view transformation
  Given from ← point(1, 3, 2)
    And to ← point(4, -2, 8)
    And up ← vector(1, 1, 0)
  When t ← view_transform(from, to, up)
  Then t is the following 4x4 matrix:
      | -0.50709 | 0.50709 |  0.67612 | -2.36643 |
      |  0.76772 | 0.60609 |  0.12122 | -2.82843 |
      | -0.35857 | 0.59761 | -0.71714 |  0.00000 |
      |  0.00000 | 0.00000 |  0.00000 |  1.00000 |
*/
