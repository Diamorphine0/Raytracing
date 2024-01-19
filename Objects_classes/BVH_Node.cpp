//
// Created by tudor on 19/01/24.
//

#include "BVH_Node.h"
#include <algorithm>
#include <memory>

bool BVH_Node::hit(const Ray &r, const Interval &restriction, HitRecord &rec) const {
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

BVH_Node::BVH_Node(std::vector<std::shared_ptr<Object>> &obj, int left, int right) {
    if(right - left == 1){
        // To check which is faster
        leftSon =  obj[left];
        rightSon = nullptr;
        boundingBox = leftSon->get_boundingBox();
    }
    else if(right - left == 2){
        leftSon = obj[left];
        rightSon = obj[left + 1];
        boundingBox = AxisAlignedBoundingBox(obj[left]->get_boundingBox(), obj[right]->get_boundingBox());
    }
    else {
        //make sure that the partitionScheme actually does split and doesnt produce half edges
        int partition_pos = partitionScheme(obj, left, right);

        leftSon = std::make_shared<BVH_Node>(obj, left, partition_pos);
        rightSon = std::make_shared<BVH_Node>(obj, partition_pos, right);
    }
}

/*
 * Used to sort custom
 */
struct BVH_Node_compare{
    int axis_number;
    bool min_sort;
    BVH_Node_compare(int i, bool _sort_type): axis_number(i), min_sort(_sort_type) {}

    bool operator() (const std::shared_ptr<Object> &a, const std::shared_ptr<Object> &b){
        if(min_sort)
            return a->get_boundingBox().get_ax(axis_number).min_compare(b->get_boundingBox().get_ax(axis_number));
        else
            return a->get_boundingBox().get_ax(axis_number).max_compare(b->get_boundingBox().get_ax(axis_number));
    }
};

int BVH_Node::partitionScheme(std::vector<std::shared_ptr<Object>> &obj, int left, int right) {
    std::uniform_int_distribution distrib02(0, 2);
    std::uniform_int_distribution distrib01(0, 1);
    int axis = distrib02(rand_gen);
    bool sort_min = distrib01(rand_gen);
    int median = (right - left) / 2;
    std::nth_element( (obj.begin() + left), (obj.begin() + median),(obj.begin() + right), BVH_Node_compare(axis, sort_min));
    return median;
}