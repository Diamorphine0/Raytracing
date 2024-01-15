#include "Triangle.h"

void Triangle::computeNormal() {
    normal = (p1 - p0).cross(p2 - p0);
    //normal is not normalized for now as we don't need it to
}

void Triangle::computePlaneEquation() {
    // N*(p - p0) = 0
    // N * p - N * p0 = 0
    planeEquationCoeff = - normal.dot(p0);
}

void Triangle::computeBoundingBox() {
    Vec3 min = p0;
    Vec3 max = p0;

    min.x = std::min(min.x, p1.x);
    min.x = std::min(min.x, p2.x);
    max.x = std::max(max.x, p1.x);
    max.x = std::max(max.x, p2.x);

    min.y = std::min(min.y, p1.y);
    min.y = std::min(min.y, p2.y);
    max.y = std::max(max.y, p1.y);
    max.y = std::max(max.y, p2.y);

    min.z = std::min(min.z, p1.z);
    min.z = std::min(min.z, p2.z);
    max.z = std::max(max.z, p1.z);
    max.z = std::max(max.z, p2.z);

    boundingBox = BoundingBox(min, max);
}

Triangle::Triangle(const Point3 &a, const Point3 &b, const Point3 &c) {
    p0 = a;
    p1 = b;
    p2 = c;

    computeNormal();
    computePlaneEquation();
    computeBoundingBox();

    std::cerr<<"Normal is "<<normal<<"\n";
    std::cerr<<"THe coefficient is "<<planeEquationCoeff<<std::endl;
}

bool Triangle::checkInsideTriangle(const Point3 &p) const{
    Vec3 v0 = p0 - p, v1 = p1 - p, v2 = p2 - p;
    // We check if the triangles formed by p and the p0, p1, p2 points are always in the same order(trigo or anti-trigo)
    Vec3 n0 = v0.cross(v1);
    Vec3 n1 = v1.cross(v2);
    Vec3 n2 = v2.cross(v0);
    //if one of them points in a diff way p is not inside
    if (n0.dot(n1) <= 0)
        return false;
    if (n0.dot(n2) <= 0)
        return false;
    return true;
}

bool Triangle::checkOnPlane(const Point3 &p) const{
    if (std::abs(normal.dot(p) + planeEquationCoeff) <= EPS)
        return true;
    return false;
}

std::pair<bool, Hittable*> Triangle::intersectWithRay(const Ray &r, float &t) const{
    //Check if ray is parallel to plane of triangle
    Point3 r_origin = r.get_origin(), r_direction = r.get_direction();

    float dir_dot_normal = r_direction.dot(normal);
    if (std::abs(dir_dot_normal) <= EPS)
        return {false, NULL};

    //Compute intersection point with triangle
    // Phit * normal + coef = 0; Phit = origin + t * direction => t = -( coef + origin * normal) / (direction * normal)

    t = - (planeEquationCoeff + r_origin.dot(normal)) / dir_dot_normal;
    if(t < 0)
        return {false, NULL};
    //std::cerr<<t<<"\n";
    Point3 pHit = r_origin + r_direction * t;
    //std::cerr<<pHit<<std::endl;
    if(checkInsideTriangle(pHit))
        return {true, (Hittable*) this};
    return {false, NULL};
}








