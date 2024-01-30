#ifndef RAY_TRACING_TRIANGLE_H
#define RAY_TRACING_TRIANGLE_H

#include "Object.hpp"
#include "Ray.hpp"
#include "Utilities.hpp"
#include "Texture.h"
/**  Class to holds triangles. Holds the 3 points, the normal (normalized) and
 *      equationCoefficient (to compute intersection faster)
 */
class Triangle: public Object {
public:
    /**
     * Takes the 3 points defining a triangle.
     * For now all triangles are considered double sided.
     *
     */
    Triangle(const point3 &a, const point3 &b, const point3 &c, const vec2 &aUV, const vec2 &bUV, const vec2 &cUV, const vec3 &n0, const vec3 &n1, const vec3 &n2, const std::shared_ptr<Texture> &texture, const std::shared_ptr<Material> &material);

    virtual bool hit(const Ray &r, const Interval &restriction,  HitRecord &rec) const;



private:
    point3 p0{}, p1{}, p2{};
    vec2 p0UV{}, p1UV{}, p2UV{};
    vec3 n0{}, n1{}, n2{};
    //point3 normal{};
    float planeEquationCoeff{};

    bool checkOnPlane(const point3 &p) const;
    //assumes point is already on plane
    bool checkInsideTriangle(const point3 &p) const;

    void computeNormal();
    void computePlaneEquation();

    std::shared_ptr<Texture> texture = nullptr;
    std::shared_ptr<Material> material = nullptr;
};

#endif //RAY_TRACING_TRIANGLE_H
