#ifndef RAY_TRACING_TRIANGLE_H
#define RAY_TRACING_TRIANGLE_H

#include "hittable.hpp"
#include "ray.hpp"
#include "utilities.hpp"




class Triangle: public Hittable {
public:
    /**
     * Takes the 3 points defining a triangle.
     * For now all triangles are considered double sided.
     *
     */
    Triangle(const Point3 &a, const Point3 &b, const Point3 &c);

    virtual bool intersectWithRay(const Ray &r);

private:
    Point3 p0, p1, p2;
    Point3 normal;
    float planeEquationCoeff;

    bool checkOnPlane(const Point3 &p);
    //assumes point is already on plane
    bool checkInsideTriangle(const Point3 &p);

    void computeNormal();
    void computePlaneEquation();
};

#endif //RAY_TRACING_TRIANGLE_H
