//
// Created by tudor on 19/01/24.
//

#include "AxisAlignedBoundingBox.h"

bool AxisAlignedBoundingBox::hit(const Ray &r, Interval restriction) const {
    for(int i = 0; i < 3; i++){
        auto inv_dir (r.get_inv_direction()[i]);
        auto &itv = ax[i];

        auto t0 = (itv.min - r.get_origin()[i]) * inv_dir;
        auto t1 = (itv.max - r.get_origin()[i]) * inv_dir;

        if(inv_dir < 0)
            std::swap(t0, t1);

        if(t0 > restriction.min)
            restriction.min = t0;
        if(t1 < restriction.max)
            restriction.max = t1;
        if(restriction.max < restriction.min)
            return false;
    }
    return true;
}

AxisAlignedBoundingBox::AxisAlignedBoundingBox(const Interval &xInt, const Interval &yInt, const Interval &zInt) {
    ax[0] = xInt;
    ax[1] = yInt;
    ax[2] = zInt;
}

AxisAlignedBoundingBox::AxisAlignedBoundingBox(point3 a, point3 b) {
    for(int i = 0; i < 3; i++){
        ax[i] = Interval(std::min(a[i], b[i]), std::max(a[i], b[i]));
    }
}

AxisAlignedBoundingBox::AxisAlignedBoundingBox(const AxisAlignedBoundingBox &a, const AxisAlignedBoundingBox &b) {
    for(int i = 0; i < 3; i++){
        ax[i] = Interval(a.get_ax(i), b.get_ax(i));
    }
}


