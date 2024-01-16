#include "Dielectric.h"

Ray Dielectric::scatter(const Ray & ray, Vec3 intersection, Vec3 normal){
    Ray resultantRay = refract(ray, intersection, normal);

    return resultantRay;
}

Ray Dielectric::refract(const Ray & ray, Vec3 intersection, Vec3 normal){

    double indicesRatio_IT = ray.get_currentMediumIndex()/refractiveIndex;

    Vec3 incidentDirection = ray.get_direction();
    if (incidentDirection.dot(normal)>0) {
        normal = normal *(-1);
    }

    auto cosIncidence = (incidentDirection*(-1)).dot(normal);


    return Ray(intersection, incidentDirection, ray.get_reflectionDepth()+1);

}
