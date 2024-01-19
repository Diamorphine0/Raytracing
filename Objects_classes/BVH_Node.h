//
// Created by tudor on 19/01/24.
//

#ifndef RAY_TRACING_BVH_NODE_H
#define RAY_TRACING_BVH_NODE_H
#include "Utilities.hpp"
#include "Object.hpp"
#include "Objects_List.h"
#include <memory>

class BVH_Node: public Object {
public:
    /**
     *Left included, right excluded.
     */
    BVH_Node(std::vector<std::shared_ptr<Object>> &obj, int left, int right);
    BVH_Node(const Objects_List & ol) {
        auto list_objects = ol.get_list();
        *this = BVH_Node(list_objects, 0, list_objects.size());
    }
    virtual bool hit(const Ray &r, const Interval &restriction,  HitRecord &rec) const;


private:
    std::shared_ptr<Object> leftSon = nullptr;
    std::shared_ptr<Object> rightSon = nullptr;

    /**
     * Partitions [left, right) and modifies the list into two and returns the ("middle") index, putting everything (less than) on the left and (bigger than) after..
     * For now uses randomized axis picking and splitting by the median.
     * Can be improved (SAH algorithm).
     */
    int partitionScheme(std::vector<std::shared_ptr<Object>> &obj, int left, int right);
};


#endif //RAY_TRACING_BVH_NODE_H
