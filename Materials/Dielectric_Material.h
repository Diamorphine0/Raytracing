#ifndef DIELECTRIC_H
#define DIELECTRIC_H

#include "Material.h"

//Transparent or translucent surfaces: ex. glass, water, plastic
class Dielectric : public Material {
public:
    Dielectric(const vec3& color, float reflectance, float ior)
            : Material(color, reflectance, 0.0f, ior) {}

    vec3 computeColor(const vec3& incident, const vec3& normal, float ior) const override {
        return getColor();
    }

    Ray scatter(const vec3& hit_point, const vec3& normal, const vec3& incident) const override {
        vec3 reflected_dir = reflect(incident, normal);
        std::uniform_real_distribution<> dis(0, 1.0);

        float reflection_prob = fresnelSchlick(incident, normal, getIOR());

        if (dis(rand_gen) < reflection_prob) {
            return Ray(hit_point, reflected_dir); // Reflect
        } else {
            vec3 refracted_dir = refract(incident, normal, getIOR());
            return Ray(hit_point, refracted_dir); // Refract
        }
    }
};


#endif // DIELECTRIC_H