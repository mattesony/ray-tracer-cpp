#ifndef LIGHT_H
#define LIGHT_H

#include <Eigen/Eigen>

using namespace Eigen;

struct Light
{
    Vector3f X;
    Vector3f La;
    Vector3f Li;
    float F;
    float K;
};

#endif // LIGHT_H
