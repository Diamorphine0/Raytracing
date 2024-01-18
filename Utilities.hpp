#ifndef UTILITIES_HPP
#define UTILITIES_HPP
#include <cmath>
#include <iostream>
#include <glm/glm.hpp>
#include <random>
using namespace glm;
using point3 = vec3; // For clarity
using color3 = vec3;

extern std::mt19937 rand_gen;


const float INF = std::numeric_limits<float>::infinity();
const float EPS = 1e-7;
#endif // UTILITIES_HPP
