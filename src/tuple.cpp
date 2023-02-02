#include "tuple.h"

Vector4f point(float x, float y, float z) { return Vector4f(x, y, z, 1); }

bool isPoint(Vector4f tuple) { return tuple(3) == 1; }

Vector4f vector(float x, float y, float z) { return Vector4f(x, y, z, 0); }

bool isVector(Vector4f tuple) { return tuple(3) == 0; }

Vector3f color(float r, float g, float b) { return {r, g, b}; }

Vector4f reflect(Vector4f in, Vector4f normal) {
  return in - normal * 2 * in.dot(normal);
}
