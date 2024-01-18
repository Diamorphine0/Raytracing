#ifndef LIGHT_H
#define LIGHT_H
#include "Utilities.hpp"
#include "Material.h"

class DiffuseLight : public Material {
public:
    DiffuseLight(Color c) {emitted = c; isLight = true;}
    Color getEmitted() {return emitted;}



private:
    Color emitted;
};


#endif // LIGHT_H
