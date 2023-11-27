#include "ray.hpp"

Ray::Ray(Vec3 direction) {
    dir = direction;
}

Ray::Ray(Vec3 direction, int ref) {
    dir = direction; reflection_depth = ref;
}
