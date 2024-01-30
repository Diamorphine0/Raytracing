#ifndef MATERIAL_H
#define MATERIAL_H

#include "Ray.hpp"
#include "HitRecord.h"
struct HitRecord;
/**
 * Abstract class for material.
 */
class Material {
public:
    //By default assume materials are not lights
    virtual color3 light_emitted(HitRecord &r) { return {0, 0, 0}; };

    //works similarly to hit. returns true/false if there is a new ray generated and some useful parameters
    virtual bool scatter(const Ray &r, const HitRecord &rec, color3 &attenuation, Ray &secondary_ray) = 0;

protected:
    Material() { };

    static vec3 reflect(const vec3 &incident, const vec3 &normal) {
        return incident - 2 * glm::dot(incident, normal) * normal;
    }
    //by Snell's law
    static vec3 refract(const vec3 &incident, const vec3 &normal, float ior, bool &can_refract) {
        float cos_theta = std::min(1.0f, dot(-incident, normal));
        float sin = ior * ior * (1.0 - cos_theta - cos_theta);
        if (sin > 1.0)
            can_refract = false; //can't refract, must reflect

        can_refract = true;
        vec3 r_perp = ior * (incident + cos_theta * normal);
        vec3 r_paralel = -glm::sqrt(glm::abs(1.0f - glm::length2(r_perp))) * normal;
        return r_perp + r_paralel;
    }
};

#endif // MATERIAL_H