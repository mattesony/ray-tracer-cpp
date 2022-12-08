#ifndef VECTOR_H
#define VECTOR_H

#include <Eigen/Eigen>
#include "tuple.h"
using namespace Eigen;

struct Vector : Tuple
{
    Vector(std::initializer_list<float> list)
    {
        assert(list.size() == 3);
        auto iter = list.begin();
        x = *iter++;
        y = *iter++;
        z = *iter;
    }

    Vector fromVector(Vector3f vector)
    {
        Vector p = {vector(0), vector(1), vector(2)};
        return p;
    }

    Vector fromVector(Vector4f vector)
    {
        Vector p = {vector(0), vector(1), vector(2)};
        return p;
    }

    void operator=(Tuple tuple)
    {
        x = tuple.x;
        y = tuple.y;
        z = tuple.z;
    }

    Vector4f get4f()
    {
        Vector4f v;
        v << x, y, z, 0;
        return v;
    }

    float getMagnitude()
    {
        Vector3f v = get3f();
        return v.norm();
    }

    Vector getNormalized()
    {
        Vector3f v = get3f();
        return fromVector(v.normalized());
    }

    float dot(Vector &b)
    {
       return get3f().dot(b.get3f());
    }

    Vector cross(Vector &b)
    {
       return fromVector(get3f().cross(b.get3f()));
    }
};
#endif //VECTOR_H
