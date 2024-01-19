//
// Created by tudor on 20/01/24.
//

#ifndef RAY_TRACING_TRIANGLEMESH_H
#define RAY_TRACING_TRIANGLEMESH_H
#include "Object.hpp"
#include "Entity.h"
#include "BVH_Node.h"
/**
 * Class that can represent the mesh from the engine for the raytracing part.
 */
class TriangleMesh : public Object{
    /**
     * Assume e is already at the right frame.
     * @param e
     */
    TriangleMesh(const Entity &e);

    virtual bool hit(const Ray &r, const Interval &restriction,  HitRecord &rec) const;

private:
    std::shared_ptr<BVH_Node> triangles;
};


#endif //RAY_TRACING_TRIANGLEMESH_H
