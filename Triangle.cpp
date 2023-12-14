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

Triangle::Triangle(const Point3 &a, const Point3 &b, const Point3 &c) {
    p0 = a;
    p1 = b;
    p2 = c;

    computeNormal();
    computePlaneEquation();

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

bool Triangle::intersectWithRay(const Ray &r, float &t) const{
    //Check if ray is parallel to plane of triangle
    Point3 r_origin = r.get_origin(), r_direction = r.get_direction();

    float dir_dot_normal = r_direction.dot(normal);
    if (std::abs(dir_dot_normal) <= EPS)
        return false;

    //Compute intersection point with triangle
    // Phit * normal + coef = 0; Phit = origin + t * direction => t = -( coef + origin * normal) / (direction * normal)

    t = - (planeEquationCoeff + r_origin.dot(normal)) / dir_dot_normal;
    if(t < 0)
        return false;
    //std::cerr<<t<<"\n";
    Point3 pHit = r_origin + r_direction * t;
    //std::cerr<<pHit<<std::endl;
    if(checkInsideTriangle(pHit))
        return true;
    return false;
}

bool Triangle::intersectWithRayMT(const Ray &r, Vec3& intersectionPoint, Vec3& barycentricCoords) const{
    //Epislon here has the same definition as in math in general, it goes to 0
    const float EPSILON = 0.000001f;

    //Defining the two vectors 'e1' and 'e2' representing the edges of the triangle
    Vec3 e1 = p1 - p0;
    Vec3 e2 = p2 - p0;
    Vec3 h = e2.cross(r.get_direction());

    //Calculating the determinant 'det'
    float a = e1.dot(h);
    if (a > -EPSILON && a < EPSILON)
        // In this case there is no intersection, ray is parallel to the triangle
        return false;
    //Inverse determinante
    float f = 1.0f / a;

    Vec3 s = r.get_origin() - p0;
    float u = f * s.dot(h);
    if (u < 0.0f || u > 1.0f)
        return false;  // No intersection

    Vec3 q = e1.cross(s);
    float v = f * q.dot(r.get_direction());
    if (v < 0.0f || u + v > 1.0f)
        return false;  // No intersection

    float t = f * e2.dot(e2);

    if (t > EPSILON) {
        //Intersection is found, compute intersection point and barycentricCoords
        //Additionaly if you are reading this part and dont know what barycentricCoords are read online
        intersectionPoint = r.get_origin() + r.get_direction() * t;
        barycentricCoords = {1.0f - u - v, u, v};
        return true;
    }
    //Again there are no intersections here
    return false;
}








