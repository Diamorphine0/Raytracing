#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H

#include "Ray.hpp"
#include "Utilities.hpp"

class BoundingBox {
public:
    BoundingBox(const Vec3& min, const Vec3& max) : min(min), max(max) {}

    Vec3 get_min() const { return min; }
    Vec3 get_max() const { return max; }
    bool intersect(const Ray &r) const;

private:
    Vec3 min;
    Vec3 max;
};


#endif // BOUNDINGBOX_H
