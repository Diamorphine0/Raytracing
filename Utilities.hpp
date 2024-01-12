#ifndef UTILITIES_HPP
#define UTILITIES_HPP
#include <cmath>
#include <iostream>
#include <glm/glm.hpp>

class Vec3 {
public:
    float x, y, z;

    // Constructors
    Vec3(float x, float y, float z);
    Vec3(glm::vec3);
    Vec3();

    // Operator Overloading
    Vec3 operator+(const Vec3& other) const;
    Vec3 operator-(const Vec3& other) const;
    Vec3 operator-() const;
    Vec3 operator*(float scalar) const;
    Vec3 operator/(float scalar) const;

    // Utility Function
    float lengthSquared() const;
    float length() const;

    Vec3 cross(const Vec3&) const;
    float dot(const Vec3& other) const;

    void normalize();

};

using Point3 = Vec3; // For clarity
std::ostream& operator<< (std::ostream& stream, const Vec3& p);

Vec3 random_unit_vector();

using Color = Vec3;

const float EPS = 1e-4;
#endif // UTILITIES_HPP
