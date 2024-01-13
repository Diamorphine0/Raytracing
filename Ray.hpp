#ifndef RAY_HPP
#define RAY_HPP
#include "Utilities.hpp"

class Ray
{
public:
    Ray(Point3 c_origin, Vec3 c_direction, double c_time = 0.0, int c_reflectionDepth = 0) : origin(c_origin),
    direction(c_direction),
    reflectionDepth(c_reflectionDepth),
    time(c_time) {currentMediumIndex = 1.00;}

   ///Getters
    Point3 get_origin() const { return origin; }
    Vec3 get_direction() const { return direction; }
    int get_reflectionDepth() const { return reflectionDepth; }
    double get_time() const {return time; }

    int reflectionDepth;
    double currentMediumIndex;

protected:
    Point3 origin;
    Vec3 direction;
    double time;


};

#endif // RAY_HPP
