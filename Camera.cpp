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
            pixel_color = Color(static_cast<int>(pixel_color.x),static_cast<int>(pixel_color.y),static_cast<int>(pixel_color.z));

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
    //Stop collecting info after 3 reflections and assume ray is too weak
    if (r.get_reflectionDepth()>3) {return Color(0,0,0);}

    auto world_ans = world->intersectWithRay(r, t);
    if (world_ans.first) {




        //Object  hit and its information for scattering and coloring by material
        Hittable& objectHit = (*world_ans.second);
        //The object unit normal for scattering
        Vec3 objectNormal = objectHit.normal;
        objectNormal.normalize();
        //Material which performs attenuation of color as well as scattering
        Material& objectMaterial = objectHit.mat;


        //I need the intersection to scatter



        Point3 r_origin = r.get_origin(), r_direction = r.get_direction();

        float dir_dot_normal = r_direction.dot(objectNormal);

        //Compute intersection point with triangle
        // Phit * normal + coef = 0; Phit = origin + t * direction => t = -( coef + origin * normal) / (direction * normal)

        t = - (objectHit.planeEquationCoeff + r_origin.dot(objectNormal)) / dir_dot_normal;

        Vec3 intersection = r_origin + r_direction * t;

        //We can now scatter the ray according to material MAKE SURE THAT SCATTER INCREMENTS REFLECTION DEPTH
        Ray scatteredRay = objectMaterial.scatter(r, intersection, objectNormal);
        // We now backtrack ray color as it came from source and hit it with attenuation recursively for each object in its path
        Color resultant = ray_color(scatteredRay,world);
        objectMaterial.attenuate(resultant);
        return resultant;

    }
    else{
        //For now we have intense light sources surrounding the scene
        return Color(140, 140, 255);
    }

}
