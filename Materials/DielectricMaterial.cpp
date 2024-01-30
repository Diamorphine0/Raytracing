#include "DielectricMaterial.h"

bool DielectricMaterial::scatter(const Ray &r, const HitRecord &rec, color3 &attenuation, Ray &secondary_ray) {
    attenuation = vec3{1.0f, 1.0f, 1.0f};
    float cor_ior = ior;
    if(!rec.frontFace)
        cor_ior = 1.0f/ior;

    auto unit_dir = glm::normalize(r.get_direction());

    vec3 dir;
    bool can_refract = true;
    auto refracted = refract(unit_dir, rec.normal, cor_ior, can_refract);

    std::uniform_real_distribution<float> dis(0, 1);
    if(!can_refract || fresnelSchlick_reflectance(unit_dir, rec.normal, cor_ior) > dis(rand_gen))
        dir = reflect(unit_dir, rec.normal);
    else
        dir = refracted;

    secondary_ray = Ray(rec.pointHit, dir);
    return true;
}
