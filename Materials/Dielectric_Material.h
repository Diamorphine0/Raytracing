#ifndef DIELECTRIC_H
#define DIELECTRIC_H

#include "Material.h"

//Transparent or translucent surfaces: ex. glass, water, plastic
class DielectricMaterial : public Material {
public:
    DielectricMaterial(const vec3& color, float ior)
            : Material(color, 0.0f, 1.0f, ior) {}

    // Override the computeColor function to implement dielectric behavior
    virtual vec3 computeColor(const vec3& incident, const vec3& normal, float ior) const override {
        vec3 reflected = reflect(incident, normal);
        vec3 refracted = refract(incident, normal, ior);

        float fresnelFactor = fresnelSchlick(incident, normal, ior);

        vec3 finalColor = (1.0f - fresnelFactor) * computeRefraction(refracted) +
                          fresnelFactor * computeReflection(reflected);

        return finalColor;
    }
};

#endif // DIELECTRIC_H