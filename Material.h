#ifndef MATERIAL_H
#define MATERIAL_H

#include "Utilities.hpp"
#include "Ray.hpp"

class Material
{
public:
    Material() {};

    virtual Ray scatter(const Ray&, Vec3, Vec3) = 0;

    Color attenuation;

    void attenuate(Color& color) {
        color.x = attenuation.x * color.x;
        color.y = attenuation.y * color.y;
        color.z = attenuation.z * color.z;
    }

    bool isLight = false;

    virtual Color getEmitted(Vec3 dir) {return Color(0,0,0);}


protected:


};

#endif // MATERIAL_H
