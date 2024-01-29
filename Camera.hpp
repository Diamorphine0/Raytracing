#ifndef CAMERA_Hpp
#define CAMERA_Hpp

#include "Object.hpp"
#include "Ray.hpp"
#include "Utilities.hpp"
#include "ImageRenderer.h"
#include <memory>

class Camera {
public:
    Camera(int height, int width, const point3 &position) : imageRenderer(height, width), lookfrom(position) {  }

    void render(std::shared_ptr<Object> world, const std::string &imagepath);

    double vfov = 90;  // Vertical field of view

    //Positioning camera
    point3 lookfrom;                          // Point camera is looking from
    point3 lookat = point3(0,0,1);   // Point camera is looking at
    vec3   vup = vec3(0,1,0);        // "up" direction

private:
    ImageRenderer imageRenderer;

    point3 center;         // Camera center
    point3 pixel00_loc;    // Location of pixel 0, 0

    // Camera frame basis vectors
    vec3   u;
    vec3   v;
    vec3   w;

    vec3 pixel_delta_u;  // Offset to pixel to the right
    vec3 pixel_delta_v;  // Offset to pixel below

    void initialize();

    color3 ray_color(const Ray& r, const std::shared_ptr<Object> &world, int depth) const;
};

#endif // CAMERA_Hpp

