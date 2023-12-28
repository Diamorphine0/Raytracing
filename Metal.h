#ifndef METAL_H
#define METAL_H

#include "Material.h"


class Metal : public Material
{
public:
    Metal(Color att, double smooth) {attenuation = att;smoothness = smooth;}

    virtual Ray scatter(const Ray&, Vec3, Vec3);

    double smoothness;

protected:

};

#endif // METAL_H
