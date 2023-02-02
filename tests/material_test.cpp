#include "../src/material.h"

#include "../src/light.h"
#include "./testing_tools.h"
#include "gmock/gmock.h"

using ::testing::FloatEq;

TEST(MaterialTest, Default) {
  /*
  Scenario: The default material
  */
  auto m = Material();
  EXPECT_EQ(m.color, Vector3f(1, 1, 1));
  ASSERT_THAT(m.ambient, FloatEq(0.1));
  ASSERT_THAT(m.diffuse, FloatEq(0.9));
  ASSERT_THAT(m.specular, FloatEq(0.9));
  ASSERT_THAT(m.shininess, FloatEq(200));
}

TEST(MaterialTest, EyeBetweenLightAndSurface) {
  /*
  Scenario: Lighting with the eye between the light and the surface
  */
  auto m = Material();
  auto position = point(0, 0, 0);
  auto eyev = vector(0, 0, -1);
  auto normalv = vector(0, 0, -1);
  auto light = Light(point(0, 0, -10), {1, 1, 1});
  compareColors(lighting(m, light, position, eyev, normalv),
                color(1.9, 1.9, 1.9));
}

TEST(MaterialTest, EyeBetweenLightAndSurfaceEyeOffset45) {
  /*
  Scenario: Lighting with the eye between light and surface, eye offset 45°
  */
  auto m = Material();
  auto position = point(0, 0, 0);
  auto eyev = vector(0, sqrt(2) / 2, -sqrt(2) / 2);
  auto normalv = vector(0, 0, -1);
  auto light = Light(point(0, 0, -10), {1, 1, 1});
  compareColors(lighting(m, light, position, eyev, normalv), color(1, 1, 1));
}

TEST(MaterialTest, EyeOppositeSurfaceLightOffset45) {
  /*
  Scenario: Lighting with eye opposite surface, light offset 45°
  */
  auto m = Material();
  auto position = point(0, 0, 0);
  auto eyev = vector(0, 0, -1);
  auto normalv = vector(0, 0, -1);
  auto light = Light(point(0, 10, -10), {1, 1, 1});
  compareColors(lighting(m, light, position, eyev, normalv),
                color(0.7364, 0.7364, 0.7364));
}

TEST(MaterialTest, EyeInPathOfReflection) {
  /*
  Scenario: Lighting with eye in the path of the reflection vector
  */
  auto m = Material();
  auto position = point(0, 0, 0);
  auto eyev = vector(0, -sqrt(2) / 2, -sqrt(2) / 2);
  auto normalv = vector(0, 0, -1);
  auto light = Light(point(0, 10, -10), {1, 1, 1});
  compareColors(lighting(m, light, position, eyev, normalv),
                color(1.6364, 1.6364, 1.6364));
}

TEST(MaterialTest, LightBehindSurface) {
  /*
  Scenario: Lighting with the light behind the surface
  */
  auto m = Material();
  auto position = point(0, 0, 0);
  auto eyev = vector(0, 0, -1);
  auto normalv = vector(0, 0, -1);
  auto light = Light(point(0, 0, 10), {1, 1, 1});
  compareColors(lighting(m, light, position, eyev, normalv),
                color(0.1, 0.1, 0.1));
}
