#ifndef RAY_TRACING_TRIANGLE_H
#define RAY_TRACING_TRIANGLE_H

#include "Object.hpp"
#include "Ray.hpp"
#include "Utilities.hpp"
/**  Class to holds triangles. Holds the 3 points, the normal (normalized) and
 *      equationCoefficient (to compute intersection faster)
 *
 */
class Triangle: public Object {
public:
    /**
     * Takes the 3 points defining a triangle.
     * For now all triangles are considered double sided.
     *
     */
    Triangle(const point3 &a, const point3 &b, const point3 &c, color3 color);
    Triangle(const point3 &a, const point3 &b, const point3 &c, const point3 &normal, color3 color);

    virtual bool hit(const Ray &r, const Interval &restriction,  HitRecord &rec) const;

    ///TEMPORARY
    color3 color;

private:
    point3 p0{}, p1{}, p2{};
    point3 normal{};
    float planeEquationCoeff{};

    bool checkOnPlane(const point3 &p) const;
    //assumes point is already on plane
    bool checkInsideTriangle(const point3 &p) const;

    void computeNormal();
    void computePlaneEquation();
};

#endif //RAY_TRACING_TRIANGLE_H
