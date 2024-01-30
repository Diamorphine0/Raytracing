#ifndef DIELECTRIC_H
#define DIELECTRIC_H

#include "Material.h"
#include "Texture.h"

//Transparent or translucent surfaces: ex. glass, water, plastic
class DielectricMaterial : public Material {
public:
    DielectricMaterial(float _ior) : ior(_ior) {}


    virtual bool scatter(const Ray &r, const HitRecord &rec, color3 &attenuation, Ray &secondary_ray);
private:
    //index of refraction
    float ior;

    // Fresnel-Schlick approximation for reflection intensity
    static float fresnelSchlick_reflectance(const vec3 &incident, const vec3 &normal, float cor_ior){
        float r0 = pow((1.0 - cor_ior) / (1.0 + cor_ior), 2.0); // Reflectance at normal incidence
        float cos_theta = std::min(1.0f, dot(-incident, normal));
        return r0 + (1.0 - r0) * pow(1.0 - cos_theta, 5.0);
    }
};


#endif // DIELECTRIC_H