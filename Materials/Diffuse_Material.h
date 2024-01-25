#ifndef DIFFUSE_MATERIAL_H
#define DIFFUSE_MATERIAL_H

#include "Materials.h"

//Reflect light uniformly, non-glossy surfaces: ex. wood, earth, cotton
class DiffuseMaterial : public Material {
public:
    DiffuseMaterial(const vec3& color, float reflectance)
            : Material(color, reflectance, 0.0, 1.0) {} // Transparency set to 0, IOR set to 1.0 (air)

    // Override the computeColor function to implement Lambertian reflection
    virtual vec3 computeColor(const vec3& incident, const vec3& normal) const override {
        float diffuseIntensity = std::max(0.0f, dot(incident, normal));
        return getColor() * diffuseIntensity;
    }
};

#endif // DIFFUSE_MATERIAL_H