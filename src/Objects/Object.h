//
// Created by Lucas on 14-05-2024.
//

#pragma once

#include "../Math/Ray.h"
#include "HitRecord.h"

class Object {
public:
    virtual ~Object() = default;

    virtual bool Hit(const Ray& ray, float rayTmin, float rayTmax, HitRecord& hit) const = 0;
};
