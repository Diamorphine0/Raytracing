#ifndef DIELECTRIC_H
#define DIELECTRIC_H


#include "Material.h"

class Dielectric : public Material
{
public:
    Dielectric(Color att, double refIndex) {attenuation = att; refractiveIndex = refIndex;}

    virtual Ray scatter(const Ray&, Vec3, Vec3);

    Ray refract(const Ray&, Vec3, Vec3);

    Ray reflect(const Ray&, Vec3, Vec3);

    double refractiveIndex;

    virtual Color getEmitted(Vec3 dir) {return Color(0,0,0);}

protected:

};

#endif // DIELECTRIC_H
