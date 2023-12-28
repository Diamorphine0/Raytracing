#ifndef DIELECTRIC_H
#define DIELECTRIC_H


#include "Material.h"

class Dielectric : public Material
{
public:
    Dielectric(Color att) {attenuation = att;}

    virtual Ray scatter(const Ray&, Vec3, Vec3);

protected:

};

#endif // DIELECTRIC_H
