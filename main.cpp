#include <vector>
#include <string>
#include "Hittable.hpp"
#include "Triangle.h"
#include "Ray.hpp"
#include "Camera.hpp"

// Define constants for image size
const int WIDTH = 800;
const int HEIGHT = 600;


// Function to check if a ray intersects with a sphere
bool raySphereIntersection(const Vec3& rayOrigin, const Vec3& rayDirection,
                           const Vec3& sphereCenter, float sphereRadius) {
    Vec3 oc = rayOrigin - sphereCenter;
    float a = rayDirection.dot(rayDirection);
    float b = 2.0f * oc.dot(rayDirection);
    float c = oc.lengthSquared() - sphereRadius * sphereRadius;
    float discriminant = b * b - 4 * a * c;
    return (discriminant > 0);
}

int main(int argc, char *argv[]) {
    Point3 p0(0.0, 0.0, -5.0);
    Point3 p1(200.0, 300.0, -5.0);
    Point3 p2(100.0, 300.0, -5.0);

    Hittable *world = new Triangle(p0, p1, p2);

    Point3 origin(0, 0, 0);
    Camera c(HEIGHT, WIDTH, origin);

    c.render(*world, "../image.ppm");

    return 0;
}
