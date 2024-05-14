//
// Created by Lucas on 14-05-2024.
//

#pragma once

#include "../Math/Ray.h"

struct HitRecord;

struct Material {
    virtual ~Material() = default;

    virtual bool Scatter(const Ray& ray, const HitRecord& hit, Vector3& attenuation, Ray& scattered) const { return false; }
};
