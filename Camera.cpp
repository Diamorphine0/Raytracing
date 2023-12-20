#include "Camera.hpp"

void Camera::render(const Hittable& world, const std::string &imagePath) {
    initialize();
    imageRenderer.reset_pixels();

    for (int j = 0; j < imageRenderer.get_height(); ++j) {
        for (int i = 0; i < imageRenderer.get_width(); ++i) {
            auto pixel_center = pixel00_loc + (pixel_delta_u * i) + (pixel_delta_v * j);
            auto ray_direction = pixel_center - center;
            Ray r(center, ray_direction);

            Color pixel_color = ray_color(r, world);

            imageRenderer.set_pixel(j, i, pixel_color);
        }
    }
    imageRenderer.render_image(imagePath);
}

void Camera::initialize() {
    center = lookfrom;

    // Determine viewport dimensions.
    auto focal_length = (lookfrom - lookat).length();
    auto theta = vfov * (M_PI / 180.0);
    auto h = tan(theta/2);
    auto viewport_height = 2 * h * focal_length;
    auto viewport_width = viewport_height * (static_cast<double>(imageRenderer.get_width())/imageRenderer.get_height());

    // Calculate the u,v,w unit basis vectors for the camera coordinate frame.
    w = (lookfrom - lookat);
    w.normalize();
    u = vup.cross(w);
    u.normalize();
    v = w.cross(u);

    // Calculate the vectors across the horizontal and down the vertical viewport edges.
    Vec3 viewport_u = u * viewport_width;    // Vector across viewport horizontal edge
    Vec3 viewport_v = -v * viewport_height;  // Vector down viewport vertical edge

    // Calculate the horizontal and vertical delta vectors from pixel to pixel.
    pixel_delta_u = viewport_u * (1.0 / imageRenderer.get_width());
    pixel_delta_v = viewport_v * (1.0 / imageRenderer.get_height());

    // Calculate the location of the upper left pixel.
    auto viewport_upper_left = center - (w * focal_length) - viewport_u/2 - viewport_v/2;
    pixel00_loc = viewport_upper_left + (pixel_delta_u + pixel_delta_v) * 0.5;
}

Color Camera::ray_color(const Ray& r, const Hittable& world) const {
    float t = 0;
    if (world.intersectWithRay(r, t)) {
        std::cerr<<"Hit at "<<r.get_direction()<<"\n";
        // we should instead be getting the color from the engine.
        return  Color (255,255,255);
    }
    else{
        return Color(0, 255, 0);
    }

}
