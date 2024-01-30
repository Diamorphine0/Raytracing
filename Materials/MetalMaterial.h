//
// Created by tudor on 30/01/24.
//

#ifndef RAY_TRACING_METALMATERIAL_H
#define RAY_TRACING_METALMATERIAL_H
#include "Material.h"
#include "Texture.h"

class MetalMaterial: public Material {
public:
    //Setting disturbance to 0 means the metal is perfect
    MetalMaterial(std::shared_ptr<Texture> &texture, float disturbance = 0.0f) : texture(texture), disturbance(disturbance) { }

    virtual bool scatter(const Ray &r, const HitRecord &rec, color3 &attenuation, Ray &secondary_ray);

private:

    std::shared_ptr<Texture> texture;
    float disturbance;
};


#endif //RAY_TRACING_METALMATERIAL_H
