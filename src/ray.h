#ifndef RAY_H_
#define RAY_H_
#include <Eigen/Eigen>
#include <algorithm>

#include "./tuple.h"

using Eigen::Matrix4f;
using Eigen::Vector4f;

class Ray {
 public:
  Vector4f origin;
  Vector4f direction;

  Ray(Vector4f origin, Vector4f direction);
  Vector4f position(float t);
  Ray transform(Matrix4f matrix);
};

#endif  // RAY_H_
