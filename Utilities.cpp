#include "Utilities.hpp"
#include <random>
#include <chrono>
//random to be used
std::mt19937 rand_gen(std::chrono::system_clock::now().time_since_epoch().count());

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

Vec3 random_unit_vector() {
// Create a random number generator and distribution
    std::uniform_real_distribution<float> distribution(0.0, 1.0);

    float x = distribution(rand_gen);
    float y = distribution(rand_gen);
    float z = distribution(rand_gen);

    Vec3 randomVector(x, y, z);
    randomVector.normalize();

    return randomVector;
}

Vec3 random_in_unit_disk() {
    std::uniform_real_distribution<float> distrib(-1 , 1);
    while (true) {
        auto p = Vec3(distrib(rand_gen), distrib(rand_gen), 0);
        if (p.lengthSquared() < 1)
            return p;
    }
}

