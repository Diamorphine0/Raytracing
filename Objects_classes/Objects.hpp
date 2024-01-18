#ifndef HITTABLE_HPP
#define HITTABLE_HPP

#include "Ray.hpp"
#include "Interval.h"
#include "HitRecord.h"
#include<memory>

class HitRecord;
/// This is the  abstract class for objects (which pretty much means anything).
class Objects {
public:
    /** Checks if ray intersects object. If true Puts all required information in rec. If false, doesn't modify rec.
     *
     * @param r The ray with which to intersect.
     * @param restriction The interval on which to intersect
     * @param rec puts all information related to the hit.
     *
     * @returns pair of true/false and the pointer to the object which it hit (if it did, otherwise null)
     */
    virtual bool hit(const Ray &r, const Interval &restriction,  HitRecord &rec) const = 0;

    //Will probably be needed
    // make bvh

protected:
    //to add materials
    Objects() {};
};

#endif // HITTABLE_HPP
