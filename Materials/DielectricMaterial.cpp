#include "DielectricMaterial.h"

bool DielectricMaterial::scatter(const Ray &r, const HitRecord &rec, color3 &attenuation, Ray &secondary_ray) {
    attenuation = color3{1.0f, 1.0f, 1.0f};

    double refraction_ratio = rec.frontFace ? (1.0/ior) : ior;

    vec3 unit_direction = glm::normalize(r.get_direction());
    double cos_theta = fmin(dot(-unit_direction, rec.normal), 1.0);
    double sin_theta = sqrt(1.0 - cos_theta*cos_theta);

    bool cannot_refract = refraction_ratio * sin_theta > 1.0;
    vec3 direction;

    std::uniform_real_distribution<double> dis(0.0f, 1.0f);
    if (cannot_refract )
        direction = reflect(unit_direction, rec.normal);
    else
        direction = refract(unit_direction, rec.normal, refraction_ratio);

    secondary_ray = Ray(rec.pointHit, direction);

    return true;
}
