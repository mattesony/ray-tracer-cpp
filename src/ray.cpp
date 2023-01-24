#include <stdexcept>
#include "ray.h"

Ray::Ray(Vector4f origin, Vector4f vector)
{
    if(isPoint(origin) && isVector(vector)){
        this->origin = origin;
        this->direction = vector;
    }
    else {
        throw std::invalid_argument( "Arguments must be point and vector types, respectively" );
    }
}
