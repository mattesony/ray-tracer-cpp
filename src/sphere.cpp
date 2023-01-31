#include "sphere.h"

#include <algorithm>
#include <vector>

Sphere::Sphere() {
  this->origin = point(0, 0, 0);
  this->radius = 1;
}

std::vector<float> Sphere::intersects(const Ray& ray) {
  std::vector<float> output;
  Vector4f sphereToRay = ray.origin - this->origin;

  float a = ray.direction.dot(ray.direction);
  float b = 2 * ray.direction.dot(sphereToRay);
  float c = sphereToRay.dot(sphereToRay) - 1;
  float discriminant = pow(b, 2) - 4 * a * c;

  if (discriminant < 0) return output;

  output.push_back((-b - sqrt(discriminant)) / (2 * a));
  output.push_back((-b + sqrt(discriminant)) / (2 * a));
  sort(output.begin(), output.end());

  return output;
}
