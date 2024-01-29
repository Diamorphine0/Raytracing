#include "Camera.hpp"

void Camera::render(std::shared_ptr<Object> world, const std::string &imagePath) {
    initialize();
    imageRenderer.reset_pixels();

    for (int j = 0; j < imageRenderer.get_height(); ++j) {
        for (int i = 0; i < imageRenderer.get_width(); ++i) {
            auto pixel_center = pixel00_loc + (pixel_delta_u * (float)i) + (pixel_delta_v * (float)j);
            auto ray_direction = pixel_center - center;
            Ray r(center, ray_direction);

            color3 pixel_color = ray_color(r, world);

            imageRenderer.set_pixel(j, i, pixel_color);
        }
    }
    imageRenderer.render_image(imagePath);
}

void Camera::initialize() {

    center = lookfrom;

    // Determine viewport dimensions.
    auto focal_length = (lookfrom - lookat).length();
    auto theta = vfov * PI /180;
    auto h = tan(theta/2);
    auto viewport_height = 2 * h * focal_length;
    auto viewport_width = viewport_height * (static_cast<double>(imageRenderer.get_width())/imageRenderer.get_height());

    // Calculate the u,v,w unit basis vectors for the camera coordinate frame.
    w = normalize(lookfrom - lookat);
    u = normalize(cross(vup, w));
    v = cross(w, u);

    // Calculate the vectors across the horizontal and down the vertical viewport edges.
    auto viewport_u = viewport_width * u;    // Vector across viewport horizontal edge
    auto viewport_v = viewport_height * -v;  // Vector down viewport vertical edge

    // Calculate the horizontal and vertical delta vectors from pixel to pixel.
    pixel_delta_u = viewport_u * (1.0f / imageRenderer.get_width());
    pixel_delta_v = viewport_v * (1.0f / imageRenderer.get_height());

    // Calculate the location of the upper left pixel.
    auto viewport_upper_left = center - (focal_length * w) - viewport_u*0.5 - viewport_v*0.5;
    pixel00_loc = viewport_upper_left + (pixel_delta_u + pixel_delta_v) * 0.5f;
}

color3 Camera::ray_color(const Ray& r, const std::shared_ptr<Object> &world) const {
    HitRecord rec;
    if(world->hit(r, Interval(EPS, INF), rec)){
        return rec.color;

    }
    return {0, 0,0};
}
