#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "Hittable.hpp"
#include "Ray.hpp"
#include "Utilities.hpp"
#include "ImageRenderer.h"

class Camera {
public:
    Camera(int height, int width, const Point3 &position) : imageRenderer(height, width), center(position) {  }

    void render(const Hittable& world, const std::string &imagePath);
private:
    ImageRenderer imageRenderer;

    Point3 center;         // Camera center
    Point3 pixel00_loc;    // Location of pixel 0, 0

    Vec3 pixel_delta_u;  // Offset to pixel to the right
    Vec3 pixel_delta_v;  // Offset to pixel below

    void initialize();

    Color ray_color(const Ray& r, const Hittable& world) const;
};

#endif // CAMERA_HPP

