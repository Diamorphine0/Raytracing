#ifndef MATERIAL_H
#define MATERIAL_H

#include "Utilities.hpp"
#include "Ray.hpp"

class Material
{
public:
    Material() {};

    virtual Ray scatter(Ray) {
        Ray a(Vec3(0,0,0),Vec3(1,1,1));
        return a;
    }

    Color attenuation;

protected:


};

#endif // MATERIAL_H
