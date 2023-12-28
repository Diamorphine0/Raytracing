#include "Lambertian.h"
#include <cstdlib>
#include <ctime>

Ray Lambertian::scatter(const Ray & ray, Vec3 origin, Vec3 normal){


    // Seed the random number generator
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // Generate random values for the x, y, and z components
    float x = static_cast<float>(std::rand()) / RAND_MAX * 2.0f - 1.0f;
    float y = static_cast<float>(std::rand()) / RAND_MAX * 2.0f - 1.0f;
    float z = static_cast<float>(std::rand()) / RAND_MAX * 2.0f - 1.0f;

    // Create the vector
    Vec3 randomVector(x, y, z);

    // Normalize the vector without explicitly computing the square root
    randomVector.normalize();

    if (ray.get_direction().dot(normal) > 0 ) {normal = normal * (-1);}

    Vec3 reflectionDirection = randomVector+normal;


    int newReflectionDepth = ray.get_reflectionDepth()+1;



    Ray reflected(origin,reflectionDirection,newReflectionDepth);
    return reflected;
}
