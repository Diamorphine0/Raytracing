#include "utilities.hpp"

//Defining operators of the class Vec3

// Constructors
Vec3::Vec3(float x, float y, float z) : x(x), y(y), z(z) {}

Vec3::Vec3() : x(0), y(0), z(0) {}

// Operator Overloading
Vec3 Vec3::operator+(const Vec3& other) const {
    return Vec3(x + other.x, y + other.y, z + other.z);
}

Vec3 Vec3::operator-(const Vec3& other) const {
    return Vec3(x - other.x, y - other.y, z - other.z);
}

Vec3 Vec3::operator -()const {
    return Vec3(-x,-y,-z);
}

Vec3 Vec3::operator*(float scalar) const {
    return Vec3(x * scalar, y * scalar, z * scalar);
}

float Vec3::dot(const Vec3& other) const {
    return x * other.x + y * other.y + z * other.z;
}

float Vec3::lengthSquared() const {
    return x * x + y * y + z * z;
}

void Vec3::normalize() {
    float norm = sqrtf(this->lengthSquared());
    x = x/norm;
    y = y/norm;
    z = z/norm;
}

Vec3 Vec3::cross(const Vec3& other) const {
    return Vec3( y*other.z-other.y*z, -(x*other.z-other.x*z), x*other.y-other.x*y);
}

