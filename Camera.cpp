#include "Camera.hpp"

void Camera::render(std::shared_ptr<Object> world, const std::string &imagePath) {
    initialize();
    imageRenderer.reset_pixels();

    for (int j = 0; j < imageRenderer.get_height(); ++j) {
        for (int i = 0; i < imageRenderer.get_width(); ++i) {
            auto pixel_center = pixel00_loc + (pixel_delta_u * (float)i) + (pixel_delta_v * (float)j);
            auto ray_direction = pixel_center - center;
            Ray r(center, ray_direction);

            color3 pixel_color = ray_color(r, world, 100);

            imageRenderer.set_pixel(j, i, pixel_color);
        }
    }
    imageRenderer.render_image(imagePath);
}

void Camera::initialize() {

    // Determine viewport dimensions.
    auto focal_length = 1;
    auto viewport_height = 2.0;
    auto viewport_width = viewport_height * (static_cast<double>(imageRenderer.get_width())/imageRenderer.get_height());

    // Calculate the vectors across the horizontal and down the vertical viewport edges.
    auto viewport_u = vec3(viewport_width, 0, 0);
    auto viewport_v = vec3(0, -viewport_height, 0);

    // Calculate the horizontal and vertical delta vectors from pixel to pixel.
    pixel_delta_u = viewport_u * (1.0f / imageRenderer.get_width());
    pixel_delta_v = viewport_v * (1.0f / imageRenderer.get_height());

    // Calculate the location of the upper left pixel.
    auto viewport_upper_left = center - vec3(0, 0, focal_length) - viewport_u * 0.5f - viewport_v * 0.5f;
    pixel00_loc = viewport_upper_left + (pixel_delta_u + pixel_delta_v) * 0.5f;
}


color3 Camera::ray_color(const Ray& r, const std::shared_ptr<Object>& world, int depth) const {
    // Maximum recursion depth
    if (depth <= 0) {
        return {0, 0, 0};
    }

    HitRecord rec;
    if (world->hit(r, Interval(0, INF), rec)) {
        vec3 point = rec.pointHit;
        vec3 normal = rec.normal;

        color3 materialColor = rec.material->computeColor(r.get_direction(), normal, rec.material->getIOR());

        Ray scattered_ray = rec.material->scatter(point, normal, r.get_direction());
        color3 scattered_color = ray_color(scattered_ray, world, depth - 1);

        color3 finalColor = (1.0 - rec.material->getReflectance()) * materialColor + rec.material->getReflectance() * scattered_color;

        return finalColor;
    }

    return {0, 0, 0};
}