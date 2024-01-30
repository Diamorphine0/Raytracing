//
// Created by tudor on 30/01/24.
//

#include "MetalMaterial.h"

bool MetalMaterial::scatter(const Ray &r, const HitRecord &rec, color3 &attenuation, Ray &secondary_ray) {
    auto reflected = reflect(r.get_direction(), rec.normal);
    auto perturbation = glm::sphericalRand(disturbance) + reflected;

    secondary_ray = Ray(rec.pointHit, perturbation);
    attenuation = texture->get_color_coordinates(rec.text_uv.x, rec.text_uv.y);
    if(dot(perturbation, rec.normal) > 0)
        return true;
    return false;
}
