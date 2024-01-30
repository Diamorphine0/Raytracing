#include "DiffuseMaterial.h"

bool DiffuseMaterial::scatter(const Ray &r, const HitRecord &rec, color3 &attenuation, Ray &secondary_ray) {
    auto dir = rec.normal + glm::sphericalRand(1.0f);

    if(glm::length2(dir) <= EPS)
        dir = rec.normal;
    attenuation = texture->get_color_coordinates(rec.text_uv.x, rec.text_uv.y);
    secondary_ray = Ray(rec.pointHit, dir);
    return true;
}
