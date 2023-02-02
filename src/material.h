#ifndef MATERIAL_H_
#define MATERIAL_H_

#include <Eigen/Eigen>

using Eigen::Vector3f;
class Material {
 public:
  Vector3f color;
  float ambient;
  float diffuse;
  float specular;
  float shininess;

  Material();

  bool operator==(Material const& rhs) const;
};

#endif  // MATERIAL_H_
