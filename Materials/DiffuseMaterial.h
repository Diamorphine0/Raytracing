#ifndef DIFFUSE_MATERIAL_H
#define DIFFUSE_MATERIAL_H

#include "Material.h"
#include "Texture.h"

//Lambertian shading
class DiffuseMaterial : public Material {
public:
    DiffuseMaterial(const std::shared_ptr<Texture> &mt_texture): texture(mt_texture) {};

    virtual bool scatter(const Ray &r, const HitRecord &rec, color3 &attenuation, Ray &secondary_ray);

private:
    std::shared_ptr<Texture> texture;
};
#endif // DIFFUSE_MATERIAL_H