#ifndef DIFFUSE_MATERIAL_H
#define DIFFUSE_MATERIAL_H

#include "Material.h"

class DiffuseMaterial : public Material {
public:
    DiffuseMaterial()
            : Material(0.0f, 0.0f,
                       1.0f) {} // Diffuse materials have no reflectance, transparency, and an IOR of 1.0

    Ray scatter(const vec3& hit_point, const vec3& normal, const vec3& incident) const override {
        vec3 target = hit_point + normal + diffuse(normal);
        return Ray(hit_point, target - hit_point);
    }
};
#endif // DIFFUSE_MATERIAL_H