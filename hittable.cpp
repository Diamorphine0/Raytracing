#include "hittable.hpp"

//hittable -> Triangle constructed with verteces for NOW!


void hittable::compute_set_nunit() {
    Vec3 vec1 = vertex_2 - vertex_1;
    Vec3 vec2 = vertex_3 - vertex_2;

    Vec3 normal = vec1.cross(vec2);
    normal.normalize();
    this->set_nunit(normal);
}
