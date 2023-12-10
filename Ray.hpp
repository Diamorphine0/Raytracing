#ifndef RAY_HPP
#define RAY_HPP
#include "Utilities.hpp"

class Ray
{
public:
    Ray(Point3 c_origin, Vec3 c_direction, int c_reflectionDepth = 0);

   ///Getters
   Point3 get_origin() const;
   Vec3 get_direction() const;
   Point3 at(float t) const;
   int get_reflectionDepth() const;

   ///Utility functions


protected:
    Point3 origin;
    Vec3 direction;

    int reflectionDepth;
};

#endif // RAY_HPP
