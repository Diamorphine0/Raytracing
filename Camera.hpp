#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "Hittable.hpp"
#include "Ray.hpp"
#include "Utilities.hpp"
#include "ImageRenderer.h"

class Camera {
public:
    Camera(int height, int width, const Point3 &position) : imageRenderer(height, width), center(position) {  };

    void render(const Hittable& world, const std::string &imagePath);

    double vfov = 90;                       // Vertical field of view

    Point3 lookfrom = Point3(0,0,0);  // Point camera is looking from
    Point3 lookat   = Point3(0,0,0-1);   // Point camera is looking at
    Vec3   vup      = Vec3(0,1,0);     // "up" direction


private:
    ImageRenderer imageRenderer;

    Point3 center;         // Camera center
    Point3 pixel00_loc;    // Location of pixel 0, 0

    Vec3 pixel_delta_u;  // Offset to pixel to the right
    Vec3 pixel_delta_v;  // Offset to pixel below

    void initialize();

    Color ray_color(const Ray& r, const Hittable& world) const;

    // Camera frame basis vectors
    Vec3 u;
    Vec3 v;
    Vec3 w;
};

#endif // CAMERA_HPP
