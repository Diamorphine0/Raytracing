#ifndef MAIN_HPP
#define MAIN_HPP

class Vec3 {
public:
    float x, y, z;

    // Constructors
    Vec3(float x, float y, float z);
    Vec3();

    // Operator Overloading
    Vec3 operator+(const Vec3& other) const;
    Vec3 operator-(const Vec3& other) const;
    Vec3 operator*(float scalar) const;
    float dot(const Vec3& other) const;

    // Utility Function
    float lengthSquared() const;
};

#endif // MAIN_HPP
