#include "ray.h"

#include <stdexcept>

Ray::Ray(Vector4f origin, Vector4f vector) {
  if (isPoint(origin) && isVector(vector)) {
    this->origin = origin;
    this->direction = vector;
  } else {
    throw std::invalid_argument(
        "Arguments must be point and vector types, respectively");
  }
}

Vector4f Ray::position(float t) { return this->origin + this->direction * t; }

Ray Ray::transform(Matrix4f matrix) {
  return Ray(matrix * this->origin, matrix * this->direction);
}
