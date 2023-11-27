#ifndef HITTABLE_HPP
#define HITTABLE_HPP

#include "ray.hpp"
#include "utilities.hpp"

class hittable      //We're exclusively considering triangles for now. In case we need to consider new polygons, we'll modify the class later.
{
public:
    hittable(Vec3 a, Vec3 b, Vec3 c) : vertex_1{a}, vertex_2{b}, vertex_3{c} { }

    bool hit_by(Ray);      //WE DO NOT KNOW EXACTLY HOW TO TREAT THIS YET

    void compute_set_nunit();    //Normal unit vector for facing ratio -> shading   THIS HAS TO COME DIRECTLY FROM ENGINE TO DETERMINE FACE NORMAL DIRECTION

    void set_nunit(Vec3 unit) {normal_unit = unit;}

    Vec3 get_normal_unit() {return normal_unit;}







private:
    Vec3 vertex_1, vertex_2, vertex_3;
    Vec3 normal_unit;

};

#endif // HITTABLE_HPP
