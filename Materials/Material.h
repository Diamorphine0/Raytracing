#ifndef MATERIAL_H
#define MATERIAL_H

#include "Utilities.hpp"
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
    Material(const vec3& color, float reflectance, float transparency, float ior)
            : color(color), reflectance(reflectance), transparency(transparency), ior(ior) {}

    vec3 getColor() const { return color; }
    float getReflectance() const { return reflectance; }
    float getTransparency() const { return transparency; }
    float getIOR() const { return ior; }
    bool isLight = false;

    // Compute the color of the material at a given point
    vec3 computeColor(const vec3& incident, const vec3& normal, float ior) const {
        vec3 reflected = reflect(incident, normal);
        vec3 refracted = refract(incident, normal, ior);

        // Fresnel-Schlick approximation for reflection intensity
        float reflectionIntensity = fresnelSchlick(incident, normal, ior);

        // Compute the final color as a combination of reflection and refraction
        vec3 finalColor = (1.0 - reflectance) * -computeDiffuse(normal) +
                          reflectance * (reflectionIntensity * computeReflection(reflected) +
                                         (1.0 - reflectionIntensity) * computeRefraction(refracted, transparency));

        return finalColor;
    }

private:

    vec3 color;          // Material color
    float reflectance;   // From 0 to 1
    float transparency;  // From 0 to 1
    float ior;

    vec3 reflect(const vec3& incident, const vec3& normal) const {
        return incident - 2 * dot(incident, normal) * normal;
    }

    vec3 diffuse(const vec3& normal){
        return diffuse_same_hemisphere(normal);
    }

    vec3 refract(const vec3& incident, const vec3& normal, float ior) const {
        float cos_theta = dot(-incident, normal);
        vec3 refracted;

        if (cos_theta < 0) {
            // Entering the material
            refracted = (ior * incident) + (ior * cos_theta - sqrt(1.0 - ior * ior * (1.0 - cos_theta * cos_theta))) * normal;
        } else {
            // Exiting the material
            refracted = incident;
        }

        return refracted;
    }

    // Fresnel-Schlick approximation for reflection intensity
    float fresnelSchlick(const vec3& incident, const vec3& normal, float ior) const {
        float r0 = pow((1.0 - ior) / (1.0 + ior), 2.0); // Reflectance at normal incidence
        float cos_theta = -dot(incident, normal);
        return r0 + (1.0 - r0) * pow(1.0 - cos_theta, 5.0);
    }

    vec3 computeDiffuse(const vec3& normal) const {
        float diffuseCoeff;
        vec3 diffuse = diffuse_same_hemisphere(normal);
        diffuseCoeff = glm::dot(normal, diffuse);
        diffuseCoeff = std::max(0.0f, diffuseCoeff);
        return color * diffuseCoeff;
    }

    vec3 computeReflection(const vec3& reflected) const {
        // Adjust the reflection color based on the angle of incidence
        float reflectionFactor = std::max(0.0f, dot(reflected, vec3(0.0, 1.0, 0.0))); // Assuming a light source from the top
        vec3 reflectionColor = vec3(1.0, 1.0, 1.0);  // Base reflection color (white)
        reflectionColor *= reflectionFactor;  // Modulate the color by the reflection factor

        return reflectionColor;
    }

    vec3 computeRefraction(const vec3& refracted, float transparency) const {
        vec3 refractionColor = vec3(0.0, 0.0, 1.0);  // Base refraction color (blue)
        refractionColor *= transparency;  // Modulate the color by the transparency factor

        return refractionColor;
    }


};
#endif // MATERIAL_H