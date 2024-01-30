#ifndef DIFFUSE_SPECULAR_H
#define DIFFUSE_SPECULAR_H

#include "Material.h"

//Combines diffuse and specular reflection: ex. plastic, ceramics, fabric
class DiffuseSpecularMaterial : public Material {
public:
    DiffuseSpecularMaterial(const vec3& color, float reflectance, float shininess)
            : Material(color, reflectance, 0.0f, 1.0f), shininess(shininess) {}

    // Override the computeColor function to implement diffuse-specular reflection
    virtual vec3 computeColor(const vec3& incident, const vec3& normal, float ior) const override {
        vec3 reflected = reflect(incident, normal);
        vec3 diffuseColor = computeDiffuse();
        vec3 specularColor = computeSpecular(incident, reflected, normal);

        // Combine diffuse and specular components
        vec3 finalColor = (1.0f - getReflectance()) * diffuseColor + getReflectance() * specularColor;
        return finalColor;
    }

private:
    float shininess;  // Shininess exponent for specular highlights

    // Helper method to compute the diffuse reflection color
    vec3 computeDiffuse() const {
        return getColor();  // Use the material's color as the diffuse color
    }

    // Helper method to compute the specular reflection color
    vec3 computeSpecular(const vec3& incident, const vec3& reflected, const vec3& normal) const {
        vec3 specularColor = vec3(1.0f, 1.0f, 1.0f);  // White specular color

        // Calculate the intensity of specular reflection using Phong's model
        float specularIntensity = pow(std::max(0.0f, dot(-incident, reflected)), shininess);

        return specularColor * specularIntensity;
    }

    // Other methods: reflect, refract, fresnelSchlick, etc.
};

#endif // DIFFUSE_SPECULAR_H