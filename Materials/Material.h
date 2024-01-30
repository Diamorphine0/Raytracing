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
    inline vec3 refract(const vec3& uv, const vec3& n, double etai_over_etat) {
        auto cos_theta = fmin(dot(-uv, n), 1.0);
        vec3 r_out_perp =  etai_over_etat * (uv + cos_theta*n);
        vec3 r_out_parallel = -sqrt(fabs(1.0 - glm::length2(r_out_perp))) * n;
        return r_out_perp + r_out_parallel;
    }
};

#endif // MATERIAL_H