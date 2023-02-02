#ifndef SPHERE_H_
#define SPHERE_H_

#include "./ray.h"

class Sphere {
 public:
  Vector4f origin;
  float radius;
  Matrix4f transform;

  Sphere();
  std::vector<float> intersects(Ray& ray);
  void set_transform(Matrix4f t);
};

#endif  // SPHERE_H_
