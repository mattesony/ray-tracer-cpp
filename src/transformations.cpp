#include "transformations.h"

using Eigen::Vector3f;
using Eigen::Vector4f;

Matrix4f translation(float x, float y, float z) {
  Matrix4f translate;
  translate << 1, 0, 0, x, 0, 1, 0, y, 0, 0, 1, z, 0, 0, 0, 1;
  return translate;
}

Matrix4f scaling(float alpha, float beta, float gamma) {
  Vector4f scale = {alpha, beta, gamma, 1};
  return scale.asDiagonal();
}

Matrix4f rotation(float a, Vector3f pointA, Vector3f pointB) {
  // TODO: Update to Vector4f to use normal points
  Vector3f nV = (pointB - pointA) / (pointB - pointA).norm();
  Matrix4f rotate;
  rotate << cos(a) + pow(nV(0), 2) * (1 - cos(a)),
      nV(0) * nV(1) * (1 - cos(a)) - nV(2) * sin(a),
      nV(0) * nV(2) * (1 - cos(a)) + nV(1) * sin(a), 0,
      nV(1) * nV(0) * (1 - cos(a)) + nV(2) * sin(a),
      cos(a) + pow(nV(1), 2) * (1 - cos(a)),
      nV(1) * nV(2) * (1 - cos(a)) - nV(0) * sin(a), 0,
      nV(2) * nV(0) * (1 - cos(a)) - nV(1) * sin(a),
      nV(2) * nV(1) * (1 - cos(a)) + nV(0) * sin(a),
      cos(a) + pow(nV(2), 2) * (1 - cos(a)), 0, 0, 0, 0, 1;
  return rotate;
}

Matrix4f rotation_x(float a) { return rotation(a, {0, 0, 0}, {1, 0, 0}); }

Matrix4f rotation_y(float a) { return rotation(a, {0, 0, 0}, {0, 1, 0}); }

Matrix4f rotation_z(float a) { return rotation(a, {0, 0, 0}, {0, 0, 1}); }

Matrix4f shearing(float xToY, float xToZ, float yToX, float yToZ, float zToX,
                  float zToY) {
  Matrix4f translate;
  translate << 1, xToY, xToZ, 0, yToX, 1, yToZ, 0, zToX, zToY, 1, 0, 0, 0, 0, 1;
  return translate;
}
