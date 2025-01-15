//
// Created by Lucas on 14-05-2024.
//

#pragma once

#include <cmath>
#include <iostream>
#include <limits>
#include <memory>
#include <stdexcept>

// Constants

const float infinity = std::numeric_limits<float>::infinity();
const float pi = 3.1415926535897932385f;

// Utility Functions

inline float DegreesToRadians(float degrees) {
    return degrees * pi / 180.0f;
}

float RandomFloat();

inline float RandomFloat(float min, float max) {
    return min + (max - min) * RandomFloat();
}

inline float Clamp(float min, float max, float x) {
    if (x < min) return min;
    if (x > max) return max;
    return x;
}