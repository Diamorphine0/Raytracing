#ifndef HITTABLE_HPP
#define HITTABLE_HPP

#include "ray.hpp"


/// This is the  abstract class for "hittable" objects and it's interface
/// ToDO: figure out a more advanced interface

class Hittable {
public:
    virtual bool intersectWithRay(const Ray &r) = 0;

protected:
    Hittable() {};
};

#endif // HITTABLE_HPP
