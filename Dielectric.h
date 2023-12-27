#ifndef DIELECTRIC_H
#define DIELECTRIC_H


#include "Material.h"

class Dielectric : public Material
{
public:
    Dielectric(Color att) {attenuation = att;}

    virtual Ray scatter(Ray);

protected:

};

#endif // DIELECTRIC_H
