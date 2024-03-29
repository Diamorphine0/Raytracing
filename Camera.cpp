#include "Camera.hpp"

void Camera::render(const std::shared_ptr<Object> &world, const std::string &imagePath, GLFWwindow* engineWindow) {
    initialize();
    imageRenderer.reset_pixels();

    for (int j = 0; j < imageRenderer.get_height(); ++j) {
        for (int i = 0; i < imageRenderer.get_width(); ++i) {
            color3 pixel_color = {0, 0, 0};
            for(int k = 0; k < samples_per_pixel; k++){
                Ray r = get_ray(i, j);

                pixel_color += glm::clamp( ray_color(r, world, max_depth), 0.0f, 1.0f);
            }
            pixel_color *= (1.0f/samples_per_pixel);
            imageRenderer.set_pixel(j, i, pixel_color);
        }
    }
    imageRenderer.render_image(imagePath);
}

void Camera::initialize() {

    center = lookfrom;

    // Determine viewport dimensions.
    auto focal_length = focus_dist;
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

    // Calculate the camera defocus disk basis vectors.
    auto defocus_radius = focus_dist * tan((defocus_angle / 2.0f)*PI/180.0f);
    defocus_disk_u = u * defocus_radius;
    defocus_disk_v = v * defocus_radius;
}


color3 Camera::ray_color(const Ray& r, const std::shared_ptr<Object>& world, int depth) const {
    // Maximum recursion depth
    if (depth <= 0) {
        return {0, 0, 0};
    }
    HitRecord rec;
    if(!world->hit(r, Interval(EPS, INF), rec))
        return background;

    Ray secondary_ray(vec3{0, 0, 0}, vec3{0, 0, 0});
    color3 change_in_col;
    color3 light_contribution = rec.material->light_emitted(rec);
    if(!rec.material->scatter(r, rec, change_in_col, secondary_ray))
        return light_contribution;
//    std::cerr<<"BEgin\n";
//    std::cerr<<"seconday ray: "<<glm::to_string(secondary_ray.get_direction())<<"\n";
//    std::cerr<<"point hit "<<glm::to_string(rec.pointHit)<<"\n";
//    std::cerr<<"normal "<<glm::to_string(rec.normal)<<"\n";
//    std::cerr<<"front face "<<(rec.frontFace)<<"\n";

    color3 next_contrib = ray_color(secondary_ray, world, depth - 1);

    color3 scattered_col = {change_in_col.x * next_contrib.x, change_in_col.y * next_contrib.y, change_in_col.z * next_contrib.z};
    return scattered_col + light_contribution;
}


Ray Camera::get_ray(int i, int j) const {
    // Get a randomly sampled camera ray for the pixel at location i,j.

    auto pixel_center = pixel00_loc + (pixel_delta_u * i) + (pixel_delta_v * j);
    auto disks = glm::diskRand(1.0f);
    auto pixel_sample = pixel_center + pixel_delta_u * disks.x + pixel_delta_v * disks.y;

    auto ray_origin = center;
    if (defocus_angle > 0) {
        //ray_origin is a random point in the camera defocus disk.
        auto p = glm::diskRand(1.0f);
        ray_origin = center + defocus_disk_u * p.x+ defocus_disk_v * p.y;
    }
    auto ray_direction = pixel_sample - ray_origin;
    return Ray(ray_origin, ray_direction);

}
