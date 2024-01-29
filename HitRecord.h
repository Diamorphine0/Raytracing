//
// Created by tudor on 18/01/24.
//

#ifndef RAY_TRACING_HITRECORD_H
#define RAY_TRACING_HITRECORD_H
#include "Utilities.hpp"
#include "Ray.hpp"
#include "Materials/Material.h"
#include <memory>

/**
 * This class contains all informations necessary at hit.
 */
struct HitRecord {

    float tHit;
    point3 pointHit;
    vec3 normal;
    bool frontFace;

    std::shared_ptr<Material> material;

    //temporary (should be material & texture)
    color3 color;

    /**
     * Sets the normal to be opposite to ray (and frontFace correspondently).
     * @param r ray
     * @param outsideNormal normal at point of intersection toward the outside surface.
     */
    void setNormalFace(const Ray &r, const vec3 &outsideNormal){
        if(glm::dot(r.get_direction(), outsideNormal) < 0) {
            //hit is from outside the object
            frontFace = true;
            normal = outsideNormal;
        }
        else {
            frontFace = false;
            normal = -outsideNormal;
        }
    }

};


#endif //RAY_TRACING_HITRECORD_H
