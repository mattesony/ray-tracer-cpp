#ifndef SPHERE_H_
#define SPHERE_H_

#include "./material.h"
#include "./ray.h"

class Sphere {
 public:
  Vector4f origin;
  float radius;
  Matrix4f transform;
  Material material;

  Sphere();
  std::vector<float> intersects(Ray& ray);
  void set_transform(Matrix4f t);
  Vector4f normal_at(Vector4f point) const;
};

#endif  // SPHERE_H_
