#ifndef TRANSFORMATIONS_H_
#define TRANSFORMATIONS_H_

#include <Eigen/Eigen>

using Eigen::Matrix4f;
using Eigen::Vector3f;

Matrix4f translation(float x, float y, float z);
Matrix4f scaling(float alpha, float beta, float gamma);
Matrix4f rotation(float a, Vector3f pointA, Vector3f pointB);
Matrix4f rotation_x(float a);
Matrix4f rotation_y(float a);
Matrix4f rotation_z(float a);
Matrix4f shearing(float xToY, float xToZ, float yToX, float yToZ, float zToX,
                  float zToY);

#endif  // TRANSFORMATIONS_H_
