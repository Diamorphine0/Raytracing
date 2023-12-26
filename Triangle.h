#ifndef RAY_TRACING_TRIANGLE_H
#define RAY_TRACING_TRIANGLE_H

#include "Hittable.hpp"
#include "Ray.hpp"
#include "Utilities.hpp"

class Triangle: public Hittable {
public:
    /**
     * Takes the 3 points defining a triangle.
     * For now all triangles are considered double sided.
     *
     */
    Triangle(const Point3 &a, const Point3 &b, const Point3 &c);

    virtual std::pair<bool, Hittable*> intersectWithRay(const Ray &r, float &t) const;

private:
    Point3 p0, p1, p2;
    Point3 normal;
    float planeEquationCoeff{};

    bool checkOnPlane(const Point3 &p) const;
    //assumes point is already on plane
    bool checkInsideTriangle(const Point3 &p) const;

    void computeNormal();
    void computePlaneEquation();
};

#endif //RAY_TRACING_TRIANGLE_H
