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
    static double reflectance(double cosine, double ref_idx) {
        auto r0 = (1.0-ref_idx) / (1.0+ref_idx);
        r0 = r0*r0;
        return r0 + (1.0-r0)*pow((1 - cosine),5);
    }
};


#endif // DIELECTRIC_H