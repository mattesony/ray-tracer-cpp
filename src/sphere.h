#ifndef SPHERE_H_
#define SPHERE_H_

#include "./ray.h"

class Sphere {
 public:
  Vector4f origin;
  float radius;

  Sphere();
  std::vector<float> intersects(const Ray& ray);
};

#endif  // SPHERE_H_
