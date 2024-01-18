#ifndef COLLIMATEDLIGHT_H
#define COLLIMATEDLIGHT_H

#include "Utilities.hpp"
#include "Material.h"

class CollimatedLight: public Material
{
public:
    CollimatedLight(Color c, Vec3 dir, float deg) {emitted = c; direction = dir;
        direction.normalize(); collimationDegree = deg; isLight = true;}
    virtual Color getEmitted(Vec3 dir);

private:
    Color emitted;
    Vec3 direction;
    float collimationDegree;
};

#endif // COLLIMATEDLIGHT_H
