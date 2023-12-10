#include "Ray.hpp"

Ray::Ray(const Point3& origin, const Vec3& direction)
    : origin(origin), direction(normalize(direction)) {}

const Point3& Ray::get_origin() const {
    return origin;
}

const Vec3& Ray::get_direction() const {
    return direction;
}

Point3 Ray::at(float t) const {
    return origin + t * direction;
}
