#include "sphere.h"

#include <algorithm>
#include <iostream>
#include <vector>

Sphere::Sphere()
    : origin(point(0, 0, 0)),
      radius(1),
      transform(Matrix4f::Identity()),
      material(Material()) {}

std::vector<float> Sphere::intersects(Ray& ray) {
  std::vector<float> output;
  Ray rayTrans = ray.transform(transform.inverse());
  Vector4f sphereToRay = rayTrans.origin - this->origin;
  float a = rayTrans.direction.dot(rayTrans.direction);
  float b = 2 * rayTrans.direction.dot(sphereToRay);
  float c = sphereToRay.dot(sphereToRay) - 1;
  float discriminant = pow(b, 2) - 4 * a * c;

  if (discriminant < 0) return output;

  output.push_back((-b - sqrt(discriminant)) / (2 * a));
  output.push_back((-b + sqrt(discriminant)) / (2 * a));
  sort(output.begin(), output.end());

  return output;
}

void Sphere::set_transform(Matrix4f t) { transform = t; }

Vector4f Sphere::normal_at(Vector4f point) const {
  // Transform to object space
  Vector4f objectPoint = this->transform.inverse() * point;
  Vector4f objectNormal = objectPoint - this->origin;
  // Transform back to normal space
  Vector4f worldNormal = this->transform.inverse().transpose() * objectNormal;
  worldNormal(3) = 0;
  return worldNormal.normalized();
}
