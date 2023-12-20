#include "Utilities.hpp"

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

Vec3 Vec3::operator/(float scalar) const {
    return Vec3(1/scalar * x, 1/scalar * y, 1/scalar * z);
}

float Vec3::dot(const Vec3& other) const {
    return x * other.x + y * other.y + z * other.z;
}

float Vec3::lengthSquared() const {
    return x * x + y * y + z * z;
}

float Vec3::length() const{
    return std::sqrt(this->lengthSquared());
}

void Vec3::normalize() {
    float norm = this->length();
    if(norm > 0){
        x = x/norm;
        y = y/norm;
        z = z/norm;
    }
}


Vec3 Vec3::cross(const Vec3& other) const {
    return Vec3( y*other.z-other.y*z, -(x*other.z-other.x*z), x*other.y-other.x*y);
}

Vec3::Vec3(glm::vec3 v) {
    x = v.x;
    y = v.y;
    z = v.z;
}

std::ostream &operator<<(std::ostream &out, const Vec3 &p) {
    out<<p.x<<" "<<p.y<<" "<<p.z;
    return out;
}
