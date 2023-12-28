#ifndef MATERIAL_H
#define MATERIAL_H

#include "Utilities.hpp"
#include "Ray.hpp"

class Material
{
public:
    Material() {};

    virtual Ray scatter(const Ray&, Vec3, Vec3) {
        Ray a(Vec3(0,0,0),Vec3(1,1,1));
        return a;
    }

    Color attenuation;

    void attenuate(Color& color) {
        color.x = attenuation.x * color.x;
        color.y = attenuation.y * color.y;
        color.z = attenuation.z * color.z;
    }


protected:


};

#endif // MATERIAL_H
