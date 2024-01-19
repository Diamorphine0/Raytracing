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

Triangle::Triangle(const point3 &a, const point3 &b, const point3 &c, color3 color = {0.7, 0.7, 0.7}) : p0(a), p1(b), p2(c), color(color) {
    computeNormal();
    computePlaneEquation();
    boundingBox = AxisAlignedBoundingBox(AxisAlignedBoundingBox(a, b), AxisAlignedBoundingBox(b, c));
}

Triangle::Triangle(const point3 &a, const point3 &b, const point3 &c, const point3 &_normal, color3 color) : p0(a), p1(b), p2(c), normal(_normal), color(color) {
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








