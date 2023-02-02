#ifndef TUPLE_H_
#define TUPLE_H_

#include <Eigen/Eigen>
using Eigen::Vector3f;
using Eigen::Vector4f;
struct Tuple {
  float x;
  float y;
  float z;

  Vector3f get3f() {
    Vector3f v;
    v << x, y, z;
    return v;
  }

  Tuple fromVector(Vector3f vector) {
    Tuple p = {vector(0), vector(1), vector(2)};
    return p;
  }

  Tuple fromVector(Vector4f vector) {
    Tuple p = {vector(0), vector(1), vector(2)};
    return p;
  }

  Tuple operator+(Tuple *b) {
    Vector3f result = get3f() + b->get3f();
    return fromVector(result);
  }

  Tuple operator-(Tuple *b) {
    Vector3f result = get3f() - b->get3f();
    return fromVector(result);
  }

  Tuple operator*(float factor) {
    Vector3f result = get3f() * factor;
    return fromVector(result);
  }

  Tuple operator/(float divisor) {
    Vector3f result = get3f() / divisor;
    return fromVector(result);
  }
};

Vector4f point(float x, float y, float z);
bool isPoint(Vector4f tuple);
Vector4f vector(float x, float y, float z);
bool isVector(Vector4f tuple);

Vector3f color(float r, float g, float b);

Vector4f reflect(Vector4f in, Vector4f normal);

#endif  // TUPLE_H_
