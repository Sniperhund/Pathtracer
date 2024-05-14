//
// Created by Lucas on 14-05-2024.
//

#pragma once

#include "Material.h"
#include "../Objects/HitRecord.h"

struct Lambertian : public Material {
    Lambertian(const Vector3& albedo) : m_albedo(albedo) {}

    bool Scatter(const Ray &ray, const HitRecord &hit, Vector3 &attenuation, Ray &scattered) const override {
        Vector3 scatterDirection = hit.normal + RandomNormalizedVector();

        if (scatterDirection.NearZero())
            scatterDirection = hit.normal;

        scattered = Ray(hit.origin, scatterDirection);
        attenuation = m_albedo;
        return true;
    }

private:
    Vector3 m_albedo;
};
