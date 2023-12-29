#include "Lambertian.h"
#include <cstdlib>
#include <ctime>

Ray Lambertian::scatter(const Ray & ray, Vec3 origin, Vec3 normal){

    Vec3 randUnitVector = random_unit_vector();

    Vec3 reflectionDirection = randUnitVector+normal;
    if(reflectionDirection.lengthSquared() < EPS)
        reflectionDirection = normal;
    int newReflectionDepth = ray.get_reflectionDepth()+1;

    Ray reflected(origin,reflectionDirection,newReflectionDepth);
    return reflected;
}
