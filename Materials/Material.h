#ifndef MATERIAL_H
#define MATERIAL_H

#include "Ray.hpp"



static vec3 random_vector(double min, double max){
    std::uniform_real_distribution<> dis(-1.0, 1.0);
    return vec3(dis(rand_gen),dis(rand_gen),dis(rand_gen));
};

static vec3 random_diffuse(){
    vec3 p;
    while (true){
        p = random_vector(-1, 1);
        if (glm::length(p)*glm::length(p) < 1)
            return glm::normalize(p);
    }
};

static vec3 diffuse_same_hemisphere(const vec3& normal){
    vec3 vector_to_verify = random_diffuse();
    if (glm::dot(vector_to_verify, normal) > 0)
        return vector_to_verify;
    else
        return -vector_to_verify;
};

class Material {
public:
    Material(const vec3 &color, float reflectance, float transparency, float ior)
            : color(color), reflectance(reflectance), transparency(transparency), ior(ior) {}

    vec3 getColor() const { return color; }

    //reflectance and transparency are currently redundant

    float getReflectance() const { return reflectance; }

    float getTransparency() const { return transparency; }

    float getIOR() const { return ior; }

    //probably also redundant:
    bool isLight = false;

    virtual vec3 computeColor(const vec3& incident, const vec3& normal, float ior) const = 0;
    virtual Ray scatter(const vec3& hit_point, const vec3& normal, const vec3& incident) const = 0;

    vec3 reflect(const vec3 &incident, const vec3 &normal) const {
        return incident - 2 * dot(incident, normal) * normal;
    }

    vec3 diffuse(const vec3 &normal) const {
        return diffuse_same_hemisphere(normal);
    }

    vec3 refract(const vec3 &incident, const vec3 &normal, float ior) const {
        float cos_theta = dot(-incident, normal);
        float sin = ior * ior * (1.0 - cos_theta - cos_theta);
        if (sin > 1.0)
            return reflect(incident, normal); //can't refract, must reflect

        float cos = glm::sqrt(1.0 - sin);

        vec3 refracted;
        refracted = ior * incident + (ior * cos_theta - cos) * normal;


        return refracted;
    }

    // Fresnel-Schlick approximation for reflection intensity
    float fresnelSchlick(const vec3 &incident, const vec3 &normal, float ior) const {
        float r0 = pow((1.0 - ior) / (1.0 + ior), 2.0); // Reflectance at normal incidence
        float cos_theta = -dot(incident, normal);
        return r0 + (1.0 - r0) * pow(1.0 - cos_theta, 5.0);
    }

private:

    vec3 color;          // Material color
    float reflectance;   // From 0 to 1
    float transparency;  // From 0 to 1
    float ior;





};

#endif // MATERIAL_H