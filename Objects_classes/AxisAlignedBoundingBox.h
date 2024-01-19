//
// Created by tudor on 19/01/24.
//

#ifndef RAY_TRACING_AXISALIGNEDBOUNDINGBOX_H
#define RAY_TRACING_AXISALIGNEDBOUNDINGBOX_H
#include "Utilities.hpp"
#include "Interval.h"
#include "Ray.hpp"

class AxisAlignedBoundingBox {
public:
    AxisAlignedBoundingBox() = default;
    AxisAlignedBoundingBox(const Interval &xInt, const Interval &yInt, const Interval &zInt);
    AxisAlignedBoundingBox(point3 a, point3 b);
    AxisAlignedBoundingBox (const AxisAlignedBoundingBox &a,const AxisAlignedBoundingBox &b);

    bool hit(const Ray &r, Interval restriction);

    const Interval& get_ax(int i) const {return ax[i]; }

private:
    Interval ax[3] = {};
};


#endif //RAY_TRACING_AXISALIGNEDBOUNDINGBOX_H
