#ifndef HITTABLE_HPP
#define HITTABLE_HPP

#include "Ray.hpp"
#include "Material.h"


/// This is the  abstract class for "hittable" objects and it's interface
/// ToDO: figure out a more advanced interface

class Hittable {
public:
    /** Computes if ray intersects with object and returns true/false.
     *
     * @param r The ray with which to intersect.
     * @param t Will be set to distance if function returns true.
     *
     * @returns pair of true/false and the pointer to the object which it hit (if it did, otherwise null)
     */

    virtual float getFacingRatio(const Ray &r) const {return (float) 0;}

    virtual std::pair<bool, Hittable*> intersectWithRay(const Ray &r, float &t) const = 0;

    void setMaterial(Material *mat) {this->mat=mat;}

    //JUST TO DEBUG. TO REMOVE.!
    Vec3 normal;
    Material *mat;
    float planeEquationCoeff;
protected:
    Hittable() {};

};

#endif // HITTABLE_HPP
