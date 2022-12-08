#ifndef TUPLE_H
#define TUPLE_H

#include <Eigen/Eigen>

using namespace Eigen;

struct Tuple
{
    float x;
    float y;
    float z;

    Vector3f get3f()
    {
        Vector3f v;
        v << x, y, z;
        return v;
    }

    Tuple fromVector(Vector3f vector)
    {
        Tuple p = {vector(0), vector(1), vector(2)};
        return p;
    }

    Tuple fromVector(Vector4f vector)
    {
        Tuple p = {vector(0), vector(1), vector(2)};
        return p;
    }

    Tuple operator+(Tuple &b)
    {
       Vector3f result = get3f() + b.get3f();
       return fromVector(result);
    }

    Tuple operator-(Tuple &b)
    {
       Vector3f result = get3f() - b.get3f();
       return fromVector(result);
    }

    Tuple operator*(float factor)
    {
       Vector3f result = get3f() * factor;
       return fromVector(result);
    }

    Tuple operator/(float divisor)
    {
       Vector3f result = get3f() / divisor;
       return fromVector(result);
    }
};

#endif //TUPLE_H
