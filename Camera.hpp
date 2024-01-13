#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "Hittable.hpp"
#include "Ray.hpp"
#include "Utilities.hpp"
#include "ImageRenderer.h"

class Camera {
public:
    Camera(int height, int width, const Point3 &position) : imageRenderer(height, width), center(position) {  }

    void render(Hittable* world, const std::string &imagePath);

    int    samples_per_pixel = 10;   // Count of random samples for each pixel
    double vfov     = 90;              // Vertical view angle (field of view)
    Point3 lookfrom = Point3(0,0,10);  // Point camera is looking from
    Point3 lookat   = Point3(0,0,0);   // Point camera is looking at
    Vec3   vup      = Vec3(0,1,0);     // Camera-relative "up" direction

    double defocus_angle = 0;  // Variation angle of rays through each pixel
    double focus_dist = 10;    // Distance from camera lookfrom point to plane of perfect focus

private:
    ImageRenderer imageRenderer;

    Vec3   u, v, w;        // Camera frame basis vectors

    Point3 center;         // Camera center
    Point3 pixel00_loc;    // Location of pixel 0, 0

    Vec3 pixel_delta_u;  // Offset to pixel to the right
    Vec3 pixel_delta_v;  // Offset to pixel below

    int max_depth = 10;
    void initialize();

    Color ray_color(const Ray& r, Hittable* world) const;
    Ray get_ray(int i, int j) const;
    Vec3 pixel_sample_square() const;

    Vec3   defocus_disk_u;  // Defocus disk horizontal radius
    Vec3   defocus_disk_v;  // Defocus disk vertical radius

};

#endif // CAMERA_HPP

