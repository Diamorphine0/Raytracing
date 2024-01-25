#ifndef PHONG_METAL_MATERIAL_H
#define PHONG_METAL_MATERIAL_H

#include "Material.h"

//Highly reflective and glossy materials, like metals: ex. gold, silver
class PhongMetalMaterial : public Material {
public:
    PhongMetalMaterial(const vec3& color, float ambient, float diffuse, float specular, float shininess)
            : Material(color, 0.0, 0.0, 1.0), ambient(ambient), diffuse(diffuse), specular(specular), shininess(shininess) {}

    // Override the computeColor function to implement Phong reflection
    virtual vec3 computeColor(const vec3& incident, const vec3& normal) const override {
        // Calculate ambient, diffuse, and specular components
        vec3 ambientColor = getColor() * ambient;
        vec3 diffuseColor = getColor() * diffuse * std::max(0.0f, dot(incident, normal));
        vec3 reflectedDirection = reflect(incident, normal);
        vec3 specularColor = vec3(1.0, 1.0, 1.0) * specular * std::pow(std::max(0.0f, dot(-incident, reflectedDirection)), shininess);

        return ambientColor + diffuseColor + specularColor;
    }

private:
    float ambient;    // Ambient reflectance coefficient
    float diffuse;    // Diffuse reflectance coefficient
    float specular;   // Specular reflectance coefficient
    float shininess;  // Shininess exponent for specular highlights
};

#endif // PHONG_METAL_MATERIAL_H