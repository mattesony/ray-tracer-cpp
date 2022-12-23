#include "tuple.h"

Vector4f point(float x, float y, float z) { return Vector4f(x, y, z, 1); }

bool isPoint(Vector4f tuple) { return tuple(3) == 1; }

Vector4f vector(float x, float y, float z) { return Vector4f(x, y, z, 0); }

bool isVector(Vector4f tuple) { return tuple(3) == 0; }
