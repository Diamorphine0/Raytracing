#include "Ray.hpp"
#include "Utilities.hpp"
Point3 Ray::at(float t) const{
    return origin + direction * t;
}
