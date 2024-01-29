#ifndef CAMERA_Hpp
#define CAMERA_Hpp

#include "Object.hpp"
#include "Ray.hpp"
#include "Utilities.hpp"
#include "ImageRenderer.h"
#include <memory>

class Camera {
public:
    Camera(int height, int width, const point3 &position) : imageRenderer(height, width), center(position) {  }

    void render(std::shared_ptr<Object> world, const std::string &imagepath);
private:
    ImageRenderer imageRenderer;

    point3 center;         // Camera center
    point3 pixel00_loc;    // Location of pixel 0, 0

    vec3 pixel_delta_u;  // Offset to pixel to the right
    vec3 pixel_delta_v;  // Offset to pixel below

    void initialize();

    color3 ray_color(const Ray& r, const std::shared_ptr<Object> &world, int depth) const;
};

#endif // CAMERA_Hpp

