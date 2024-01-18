#ifndef METAL_H
#define METAL_H

#include "Material.h"


class Metal : public Material
{
public:
    Metal(Color att) {attenuation = att;}

    virtual Ray scatter(const Ray&, Vec3, Vec3);

    double smoothness = 0;

    virtual Color getEmitted(Vec3 dir) {return Color(0,0,0);}

protected:

};

#endif // METAL_H
