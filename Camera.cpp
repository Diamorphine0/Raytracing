#include "Camera.hpp"

void Camera::render(Hittable *world, const std::string &imagePath) {
    initialize();
    imageRenderer.reset_pixels();

    for (int j = 0; j < imageRenderer.get_height(); ++j) {
        for (int i = 0; i < imageRenderer.get_width(); ++i) {
            Color pixel_color(0,0,0);
            for (int sample = 0; sample < samples_per_pixel; ++sample) {
                Ray r = get_ray(i, j);
                pixel_color = pixel_color + ray_color(r, world);
            }
            pixel_color = Color(static_cast<int>(pixel_color.x/samples_per_pixel),static_cast<int>(pixel_color.y/samples_per_pixel),static_cast<int>(pixel_color.z/samples_per_pixel));
            //divided by samples_per_pixel to get the final color after antialiasing
            imageRenderer.set_pixel(j, i, pixel_color);
        }
    }
    imageRenderer.render_image(imagePath);
}

void Camera::initialize() {

    center = lookfrom;

    // Determine viewport dimensions.
    auto theta = vfov * pi / 180.0;
    auto h = tan(theta/2);
    auto viewport_height = 2 * h * focus_dist;
    auto viewport_width = viewport_height * (static_cast<double>(imageRenderer.get_width())/imageRenderer.get_height());

    // Calculate the u,v,w unit basis vectors for the camera coordinate frame.
    w = (lookfrom - lookat);
    w.normalize();
    u = vup.cross(w);
    u.normalize();
    v = w.cross(u);

    // Calculate the vectors across the horizontal and down the vertical viewport edges.
    auto viewport_u = u * viewport_width;    // Vector across viewport horizontal edge
    auto viewport_v = -v * viewport_height;  // Vector down viewport vertical edge


    // Calculate the horizontal and vertical delta vectors from pixel to pixel.
    pixel_delta_u = viewport_u * (1.0 / imageRenderer.get_width());
    pixel_delta_v = viewport_v * (1.0 / imageRenderer.get_height());

    // Calculate the location of the upper left pixel.
    auto viewport_upper_left = center - ( w * focus_dist) - viewport_u/2 - viewport_v/2;
    pixel00_loc = viewport_upper_left + (pixel_delta_u + pixel_delta_v) * 0.5;

    // Calculate the camera defocus disk basis vectors.
    auto defocus_radius = focus_dist * tan((defocus_angle / 2)*pi/180);
    defocus_disk_u = u * defocus_radius;
    defocus_disk_v = v * defocus_radius;
}

Color Camera::ray_color(const Ray& r, Hittable *world) const {
    //std::cout<<world<<"\n";
    float t = 0;
    //Stop collecting info after max_Depth reflections and assume ray is too weak
    if (r.get_reflectionDepth()>max_depth) {
        return Color(0,0,0);
    }

    auto world_ans = world->intersectWithRay(r, t);
    if (world_ans.first) {
        //Object  hit and its information for scattering and coloring by material
        Hittable& objectHit = (*world_ans.second);
        //The object unit normal for scattering

        Material* objectMaterial = objectHit.mat;

        Vec3 intersection = r.get_origin() + r.get_direction() * t;
        //std::cerr<<"intersection point is: "<<intersection<<"\n";
        //We can now scatter the ray according to material MAKE SURE THAT SCATTER INCREMENTS REFLECTION DEPTH
        Ray scatteredRay = objectMaterial->scatter(r, intersection, objectHit.normal);
        //std::cerr<<"SCattered ray: "<<scatteredRay.reflectionDepth<<", "<<scatteredRay.get_direction()<<", "<<scatteredRay.get_origin()<<"\n";
        // We now backtrack ray color as it came from source and hit it with attenuation recursively for each object in its path
        Color resultant = ray_color(scatteredRay,world);

        objectMaterial->attenuate(resultant);
        //std::cerr<<resultant<<"\n";
        return resultant;

    }
    else{
        //For now we have intense light sources surrounding the scene
        return Color(215, 215, 255);
    }

}
Ray Camera::get_ray(int i, int j) const {
    // Get a randomly sampled camera ray for the pixel at location i,j.

    auto pixel_center = pixel00_loc + (pixel_delta_u * i) + (pixel_delta_v * j);
    auto pixel_sample = pixel_center + pixel_sample_square();

    auto ray_origin = center;
    if (defocus_angle > 0) {
        //ray_origin is a random point in the camera defocus disk.
        auto p = random_in_unit_disk();
        auto ray_origin = center + defocus_disk_u * p.x+ defocus_disk_v * p.y;
    }
    auto ray_direction = pixel_sample - ray_origin;
    auto ray_time = rand()/(RAND_MAX);

    return Ray(ray_origin, ray_direction, ray_time);

}

Vec3 Camera::pixel_sample_square() const {
    // Returns a random point in the square surrounding a pixel at the origin.
    auto px = -0.5 + (rand() / (RAND_MAX + 1.0));
    auto py = -0.5 + (rand() / (RAND_MAX + 1.0));
    return (pixel_delta_u * px) + (pixel_delta_v * py);
}

