#ifndef HITTABLE_HPP
#define HITTABLE_HPP

#include "Ray.hpp"

/// This is the  abstract class for "hittable" objects and it's interface
/// Todo: figure out a more advanced interface

class Hittable {
public:
    /** Computes if ray intersects with object and returns true/false.
     *
     * @param r The ray with which to intersect.
     * @param t Will be set to distance if function returns true.
     *
     * @returns pair of true/false and the pointer to the object which it hit (if it did, otherwise null)
     */
    virtual std::pair<bool, Hittable*> intersectWithRay(const Ray &r, float &t) const = 0;

    //JUST TO DEBUG. TO REMOVE.!
    Color color;

protected:
    Hittable() {};
};

#endif // HITTABLE_HPP
