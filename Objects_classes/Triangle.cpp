#include "Triangle.h"

void Triangle::computeNormal() {
    normal = glm::cross((p1 - p0), (p2 - p0));
    // normal is normalized
    glm::normalize(normal);
}

void Triangle::computePlaneEquation() {
    // N*(p - p0) = 0
    // N * p - N * p0 = 0
    planeEquationCoeff = - glm::dot(normal, p0);
}

Triangle::Triangle(const point3 &a, const point3 &b, const point3 &c, const vec2 &aUV, const vec2 &bUV, const vec2 &cUV, const std::shared_ptr<Texture> &texture) : p0(a), p1(b), p2(c), p0UV(aUV), p1UV(bUV), p2UV(cUV), texture(texture){
    computeNormal();
    computePlaneEquation();
    boundingBox = AxisAlignedBoundingBox(AxisAlignedBoundingBox(a, b), AxisAlignedBoundingBox(b, c));
}

Triangle::Triangle(const point3 &a, const point3 &b, const point3 &c, const point3 &_normal, const vec2 &aUV, const vec2 &bUV, const vec2 &cUV, const std::shared_ptr<Texture> &texture) : p0(a), p1(b), p2(c), normal(_normal), p0UV(aUV), p1UV(bUV), p2UV(cUV), texture(texture) {
    computePlaneEquation();
    boundingBox = AxisAlignedBoundingBox(AxisAlignedBoundingBox(a, b), AxisAlignedBoundingBox(b, c));
}


bool Triangle::checkInsideTriangle(const point3 &p) const{
    vec3 v0 = p0 - p, v1 = p1 - p, v2 = p2 - p;
    // We check if the triangles formed by p and the p0, p1, p2 points are always in the same order(trigo or anti-trigo)
    vec3 n0 = glm::cross(v0,v1);
    vec3 n1 = glm::cross(v1, v2);
    vec3 n2 = glm::cross(v2, v0);

    //if one of them points in a diff way p is not inside
    if (glm::dot(n0, n1) <= EPS)
        return false;
    if (glm::dot(n0, n2) <= EPS)
        return false;
    return true;
}

bool Triangle::checkOnPlane(const point3 &p) const{
    if (std::abs(glm::dot(normal, p) + planeEquationCoeff) <= EPS)
        return true;
    return false;
}
/*
bool Triangle::hit(const Ray &r, const Interval &restriction, HitRecord &rec) const{
    point3 r_origin = r.get_origin(), r_direction = r.get_direction();

    //checks if parallel to the plane
    float dir_dot_normal = glm::dot(r_direction, normal);
    if (std::abs(dir_dot_normal) <= EPS)
        return false;


    //Compute intersection point with triangle
    // Phit * normal + coef = 0; Phit = origin + t * direction => t = -( coef + origin * normal) / (direction * normal)

   auto t = - (planeEquationCoeff + glm::dot(r_origin,normal)) / dir_dot_normal;
    if(!restriction.surrounds(t))
        return false;

    auto pointHit = r_origin + r_direction * t;

    if(!checkInsideTriangle(pointHit))
        return false;

    //If we have reached this point it means we hit
    rec.pointHit = pointHit;
    rec.tHit = t;
    rec.setNormalFace(r, normal);
    rec.color = color;
    return true;
}
*/

bool Triangle::hit(const Ray &r, const Interval &restriction, HitRecord &rec) const{
    vec3 v1 = p1 - p0, v2 = p2 - p0;
    auto pvec = glm::cross(r.get_direction(), v2);
    auto det = glm::dot(v1, pvec);

    //checks if parallel to the plane
    if (std::fabs(det) <= EPS)
        return false;

    auto inv_det = 1.0/det;

    auto tvec = r.get_origin() - p0;
    auto u = glm::dot(tvec, pvec) * inv_det;
    if(u < 0 || u > 1)
        return false;

    auto qvec = glm::cross(tvec, v1);
    auto v = glm::dot(r.get_direction(), qvec) * inv_det;
    if(v < 0 || v + u > 1)
        return false;

    float t = glm::dot(r.get_direction(), qvec) * inv_det;
    if(!restriction.surrounds(t))
        return false;

    auto pointHit = r.get_origin() + r.get_direction() * t;

    //If we have reached this point it means we hit
    rec.pointHit = pointHit;
    rec.tHit = t;
    rec.setNormalFace(r, normal);

    auto texture_coord = (1 - u - v) * p0UV + u * p1UV + v * p2UV;
    if(texture != nullptr)
        rec.color = texture->get_color_coordinates(texture_coord.x, texture_coord.y);
    else
        rec.color = glm::vec3(texture_coord, 1);
    return true;
}







