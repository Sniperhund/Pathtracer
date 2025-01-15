#include "Utility.h"

#include <random>

float RandomFloat() {
    thread_local std::mt19937 gen(std::random_device{}());
    thread_local std::uniform_real_distribution<float> dist(0.0f, 1.0f);

    return dist(gen);
}