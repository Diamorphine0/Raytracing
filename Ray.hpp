#ifndef RAY_HPP
#define RAY_HPP
#include "Utilities.hpp"

class Ray
{
public:
    Ray(Point3 c_origin, Vec3 c_direction, float c_time = 0.0, int c_reflectionDepth = 0) :    origin(c_origin),
                                                                                                direction(c_direction),
                                                                                                reflectionDepth(c_reflectionDepth),
                                                                                                time(c_time),
                                                                                                currentMediumIndex(1.0) {}

   ///Getters
    Point3 get_origin() const { return origin; }
    Vec3 get_direction() const { return direction; }
    int get_reflectionDepth() const { return reflectionDepth; }
    float get_time() const { return time; }
    float get_currentMediumIndex() const { return currentMediumIndex; }

    Point3 at(float t) const;


protected:
    Point3 origin;
    Vec3 direction;
    float time;
    int reflectionDepth;
    float currentMediumIndex;



};

#endif // RAY_HPP
