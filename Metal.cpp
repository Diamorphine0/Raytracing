#include "Metal.h"

Ray Metal::scatter(const Ray & ray, Vec3 intersection, Vec3 normal){

    Vec3 rayDirection = ray.get_direction();
    if (rayDirection.dot(normal)>0) {normal = normal * (-1);}

    //Basic geometric observation

    Vec3 reflectedDirection = rayDirection - ((normal * (rayDirection.dot(normal))) * 2);
    int newReflectionDepth = ray.get_reflectionDepth()+1;

    Ray reflectedRay(intersection,reflectedDirection,newReflectionDepth);

    return reflectedRay;
}
