#ifndef METAL_H
#define METAL_H

#include "Material.h"


class Metal : public Material
{
public:
    Metal(Color att) {attenuation = att;}

    virtual Ray scatter(const Ray&, Vec3, Vec3);

protected:

};

#endif // METAL_H
