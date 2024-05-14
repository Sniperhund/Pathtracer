//
// Created by Lucas on 14-05-2024.
//

#pragma once

#include "Material.h"
#include "../Objects/HitRecord.h"

struct Metal : public Material {
    Metal(const Vector3& albedo, float roughness) : m_albedo(albedo), m_roughness(roughness < 1 ? roughness : 1) {}

    bool Scatter(const Ray &ray, const HitRecord &hit, Vector3 &attenuation, Ray &scattered) const override {
        Vector3 refleced = Reflect(ray.direction, hit.normal);
        refleced = Normalize(refleced) + (m_roughness * RandomNormalizedVector());
        scattered = Ray(hit.origin, refleced);
        attenuation = m_albedo;
        return (Dot(scattered.direction, hit.normal) > 0);
    }

private:
    Vector3 m_albedo;
    float m_roughness;
};
