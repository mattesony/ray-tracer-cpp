#ifndef LIGHT_H_
#define LIGHT_H_

#include <Eigen/Eigen>

#include "./material.h"
#include "./tuple.h"

using Eigen::Vector3f;
using Eigen::Vector4f;
class Light {
 public:
  Vector4f position;
  Vector3f intensity;
  Light(Vector4f pos, Vector3f i);
};

Vector3f lighting(Material material, Light light, Vector4f point, Vector4f eyev,
                  Vector4f normalv);

#endif  // LIGHT_H_
