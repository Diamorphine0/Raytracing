#ifndef MATERIAL_H
#define MATERIAL_H

#include "Utilities.hpp"
#include "Ray.hpp"

class Material
{
public:


    virtual Ray scatter(Ray) {
        Ray a(Vec3(0,0,0),Vec3(1,1,1));
        return a;
    }

    Color attenuation;

protected:
    Material() {};

};

#endif // MATERIAL_H
