#ifndef RAY_H_
#define RAY_H_

#include <Eigen/Eigen>

#include "./tuple.h"

using Eigen::Vector4f;

class Ray
{
    Vector4f origin;
    Vector4f direction;
public:
    Ray(Vector4f origin, Vector4f direction);
};

#endif // RAY_H_
