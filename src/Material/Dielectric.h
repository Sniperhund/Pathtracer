//
// Created by Lucas on 14-05-2024.
//

#pragma once

#include "Material.h"
#include "../Objects/HitRecord.h"

struct Dielectric : public Material {
    Dielectric(float refractionIndex) : m_refractionIndex(refractionIndex) {}

    bool Scatter(const Ray &ray, const HitRecord &hit, Vector3 &attenuation, Ray &scattered) const override {
        attenuation = Vector3(1);
        float ri = hit.frontFace ? (1.0f / m_refractionIndex) : m_refractionIndex;

        Vector3 normalizedDirection = Normalize(ray.direction);
        float cosTheta = fmin(Dot(-normalizedDirection, hit.normal), 1.0f);
        float sinTheta = sqrt(1.0f - cosTheta * cosTheta);

        bool cannotRefract = ri * sinTheta > 1.0f;
        Vector3 direction;

        if (cannotRefract || Reflectance(cosTheta, ri) > RandomFloat())
            direction = Reflect(normalizedDirection, hit.normal);
        else
            direction = Refract(normalizedDirection, hit.normal, ri);

        scattered = Ray(hit.origin, direction);
        return true;
    }

private:
    float m_refractionIndex;

    static float Reflectance(float cosine, float refractionIndex) {
        float r0 = (1 - refractionIndex) / (1 + refractionIndex);
        r0 = r0 * r0;
        return r0 + (1 - r0) * pow((1 - cosine), 5);
    }
};
