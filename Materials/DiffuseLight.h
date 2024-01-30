//
// Created by tudor on 30/01/24.
//

#ifndef RAY_TRACING_DIFFUSELIGHT_H
#define RAY_TRACING_DIFFUSELIGHT_H
#include "Material.h"

class DiffuseLight : public Material{
public:
    DiffuseLight(const color3 &c) : intensity(c) {}
    virtual color3 light_emitted(HitRecord &r) { return intensity; };

    virtual bool scatter(const Ray &r, const HitRecord &rec, color3 &attenuation, Ray &secondary_ray) { return false; };
private:
    color3 intensity;
};


#endif //RAY_TRACING_DIFFUSELIGHT_H
