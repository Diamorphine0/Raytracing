#ifndef RAY_HPP
#define RAY_HPP
#include "utilities.hpp"

class Ray
{
public:
    Ray(Vec3 direction);
    Ray(Vec3 direction, int ref);



protected:
    Vec3 dir;
    int reflection_depth;
};

#endif // RAY_HPP
