#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "Hittable.hpp"
#include "Ray.hpp"
#include "Utilities.hpp"
#include "ImageRenderer.h"

class Camera {
public:
    Camera(int height, int width, const Point3 &position, int aa_samples = 5, int m_depth = 10) : imageRenderer(height, width), center(position), samples_per_pixel(aa_samples), max_depth(10) {  }

    void render(Hittable* world, const std::string &imagePath);

private:
    ImageRenderer imageRenderer;


    int samples_per_pixel;   // Count of random samples for each pixel
    Point3 center;         // Camera center
    Point3 pixel00_loc;    // Location of pixel 0, 0

    Vec3 pixel_delta_right;  // Offset to pixel to the right
    Vec3 pixel_delta_down;  // Offset to pixel below

    int max_depth = 10;
    void initialize();

    Color ray_color(const Ray& r, Hittable* world) const;
    Ray get_ray(int row, int col) const;
    //Vec3 pixel_sample_square() const;

//    Vec3   defocus_disk_u;  // Defocus disk horizontal radius
//    Vec3   defocus_disk_v;  // Defocus disk vertical radius

};

#endif // CAMERA_HPP

