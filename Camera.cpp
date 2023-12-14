#include "Camera.hpp"

void Camera::render(Hittable *world, const std::string &imagePath) {
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

    // Determine viewport dimensions.
    auto focal_length = 1;
    auto viewport_height = 2.0;
    auto viewport_width = viewport_height * (static_cast<double>(imageRenderer.get_width())/imageRenderer.get_height());

    // Calculate the vectors across the horizontal and down the vertical viewport edges.
    auto viewport_u = Vec3(viewport_width, 0, 0);
    auto viewport_v = Vec3(0, -viewport_height, 0);

    // Calculate the horizontal and vertical delta vectors from pixel to pixel.
    pixel_delta_u = viewport_u * (1.0 / imageRenderer.get_width());
    pixel_delta_v = viewport_v * (1.0 / imageRenderer.get_height());

    // Calculate the location of the upper left pixel.
    auto viewport_upper_left = center - Vec3(0, 0, focal_length) - viewport_u * 0.5 - viewport_v * 0.5;
    pixel00_loc = viewport_upper_left + (pixel_delta_u + pixel_delta_v) * 0.5;
}

Color Camera::ray_color(const Ray& r, Hittable *world) const {
    float t = 0;

    auto world_ans = world->intersectWithRay(r, t);
    if (world_ans.first) {
        std::cerr<<"Hit at "<<r.get_direction();
        // we should instead be getting the color from the engine.
        //For now, just going to compute simple facing ratio and use to shade (Lambertian Reflectance)
        float facingRatio = std::abs(world_ans.second->getFacingRatio(r));
        float colorArg1 = world_ans.second->color.x *facingRatio;
        float colorArg2 = world_ans.second->color.y *facingRatio;
        float colorArg3 = world_ans.second->color.z *facingRatio;

        Color pixelColor(static_cast<int> (colorArg1), static_cast<int> (colorArg2), static_cast<int> (colorArg3));
        // we should instead be getting the color from the engine.
        return  pixelColor;

    }
    else{
        return Color(0, 0, 0);
    }

}
