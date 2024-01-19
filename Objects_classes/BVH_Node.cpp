//
// Created by tudor on 19/01/24.
//

#include "BVH_Node.h"

bool BVH_Node::hit(const Ray &r, const Interval &restriction, HitRecord &rec) {
    if(!boundingBox.hit(r, restriction))
        return false;
    bool hitLeft = false, hitRight = false;
    //We can remove checks if we make sure always two sons
    if(leftSon != nullptr)
        hitLeft = leftSon->hit(r, restriction, rec);

    if(rightSon != nullptr)
        hitRight = rightSon->hit(r, Interval(restriction.min, hitLeft ? rec.tHit : restriction.max), rec);

    return hitLeft || hitRight;
}
