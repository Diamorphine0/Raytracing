#include "BoundingBox.h"



bool BoundingBox::intersect(const Ray &ray) const {
    Vec3 origin = ray.get_origin();
    Vec3 direction = ray.get_direction();
    float tmin = (min.x - origin.x) / direction.x;
    float tmax = (max.x - origin.x) / direction.x;

    if (direction.x < 0.0f)
        std::swap(tmin, tmax);

    float tymin = (min.y - origin.y) / direction.y;
    float tymax = (max.y - origin.y) / direction.y;

    if (direction.y < 0.0f)
        std::swap(tymin, tymax);

    if ((tmin > tymax) || (tymin > tmax))
        return false;

    if (tymin > tmin)
        tmin = tymin;

    if (tymax < tmax)
        tmax = tymax;

    float tzmin = (min.z - origin.z) / direction.z;
    float tzmax = (max.z - origin.z) / direction.z;

    if (direction.z < 0.0f)
        std::swap(tzmin, tzmax);

    if ((tmin > tzmax) || (tzmin > tmax))
        return false;

    if (tzmin > tmin)
        tmin = tzmin;

    if (tzmax < tmax)
        tmax = tzmax;

    return tmax > std::max(tmin, 0.0f);
}
