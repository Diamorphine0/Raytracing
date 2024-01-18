#include "collimatedlight.h"

Color CollimatedLight::getEmitted(Vec3 dir) {

    Vec3 normal_dir = dir;
    normal_dir.normalize();

    float prod = dir.dot(this->direction);

    if (prod<=0){ return Color(0,0,0);}

    return (this->emitted)* (prod * (1-collimationDegree));

}
