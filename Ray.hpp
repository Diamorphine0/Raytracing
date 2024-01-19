#ifndef RAY_HPP
#define RAY_HPP
#include "Utilities.hpp"

class Ray
{
public:
    Ray(point3 c_origin, vec3 c_direction, int c_reflectionDepth = 0) : origin(c_origin),
        direction(c_direction),
        reflectionDepth(c_reflectionDepth),
        inv_direction(1.0f/c_direction){};

   ///Getters
    point3 get_origin() const { return origin; }
    vec3 get_direction() const { return direction; }
    vec3 get_inv_direction() const {return inv_direction; }
    int get_reflectionDepth() const { return reflectionDepth; }
   ///Utility functions


protected:
    point3 origin;
    vec3 direction;
    vec3 inv_direction;

    int reflectionDepth;
};

#endif // RAY_HPP
