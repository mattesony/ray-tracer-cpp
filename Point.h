#ifndef POINT_H
#define POINT_H

#include <Eigen/Eigen>
#include "Tuple.h"
using namespace Eigen;

struct Point : Tuple
{
    Point(std::initializer_list<float> list)
    {
        assert(list.size() == 3);
        auto iter = list.begin();
        x = *iter++;
        y = *iter++;
        z = *iter;
    }

    Point(Tuple tuple)
    {
        x = tuple.x;
        y = tuple.y;
        z = tuple.z;
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
        v << x, y, z, 1;
        return v;
    }
};

#endif //POINT_H
