#ifndef MATERIAL_H
#define MATERIAL_H

#include <Eigen/Eigen>

using namespace Eigen;

struct Material
{
    Vector3f Ka;
    Vector3f Kd;
    Vector3f Ks;
    float phongExponent;
};

#endif // MATERIAL_H
