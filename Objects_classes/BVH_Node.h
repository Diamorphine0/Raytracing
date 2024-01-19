//
// Created by tudor on 19/01/24.
//

#ifndef RAY_TRACING_BVH_NODE_H
#define RAY_TRACING_BVH_NODE_H
#include "Utilities.hpp"
#include "Object.hpp"
#include <memory>

class BVH_Node: public Object {

    BVH_Node(std::vector<std::shared_ptr<Object>> obj);
    virtual bool hit(const Ray &r, const Interval &restriction,  HitRecord &rec);



private:
    std::shared_ptr<Object> leftSon = nullptr;
    std::shared_ptr<Object> rightSon = nullptr;
};


#endif //RAY_TRACING_BVH_NODE_H
