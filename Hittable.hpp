#ifndef HITTABLE_HPP
#define HITTABLE_HPP

#include "Ray.hpp"


/// This is the  abstract class for "hittable" objects and it's interface
/// ToDO: figure out a more advanced interface

class Hittable {
public:
    /** Computes if ray intersects with object and returns true/false.
     *
     * @param r The ray with which to intersect.
     * @param t Will be set to distance if function returns true.
     */
    virtual bool intersectWithRay(const Ray &r, float &t) const = 0;
    virtual float getFacingRatio(const Ray &r) const {return (float) 0;}

protected:
    Hittable() {};
};

#endif // HITTABLE_HPP
