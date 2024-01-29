#ifndef UTILITIES_HPP
#define UTILITIES_HPP
#define GLM_ENABLE_EXPERIMENTAL
#include <cmath>
#include <iostream>
#include <glm/glm.hpp>
#include "glm/ext.hpp"
#include <random>
using namespace glm;
using point3 = vec3; // For clarity
using color3 = vec3;

extern std::mt19937 rand_gen;


const float INF = std::numeric_limits<float>::infinity();
const float EPS = 1e-7;
const float PI = 3.1415926535897932385;

#endif // UTILITIES_HPP
