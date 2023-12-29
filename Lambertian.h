#ifndef LAMBERTIAN_H
#define LAMBERTIAN_H

#include "Material.h"


class Lambertian : public Material {

public:
    Lambertian(Color att) {attenuation = att;}

    virtual Ray scatter(const Ray&, Vec3, Vec3);

protected:

};

#endif // LAMBERTIAN_H
