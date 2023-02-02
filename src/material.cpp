#include "material.h"

Material::Material()
    : color({1, 1, 1}),
      ambient(0.1),
      diffuse(0.9),
      specular(0.9),
      shininess(200) {}

bool Material::operator==(Material const& rhs) const {
  return color == rhs.color && ambient == rhs.ambient &&
         diffuse == rhs.diffuse && specular == rhs.specular &&
         shininess == rhs.shininess;
}
