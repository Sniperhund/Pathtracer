//
// Created by Lucas on 14-05-2024.
//

#pragma once

#include <cmath>
#include <utility>

#include "Object.h"
#include "../Material/Material.h"
#include "Material/Lambertian.h"

class Sphere : public Object {
public:
    Sphere() : Sphere(Vector3(), 1.0f, std::make_shared<Lambertian>(Vector3(1))) {}
    Sphere(const Vector3& origin, float radius, std::shared_ptr<Material> material) : m_origin(origin), m_radius(radius), m_material(material) {}

    bool Hit(const Ray &ray, float rayTmin, float rayTmax, HitRecord &hit) const override {
        Vector3 oc = m_origin - ray.origin;
        float a = ray.direction.Squared();
        float h = Dot(ray.direction, oc);
        float c = oc.Squared() - m_radius * m_radius;

        float discriminant = h * h - a * c;
        if (discriminant < 0)
            return false;

        float sqrtd = sqrt(discriminant);

        float root = (h - sqrtd) / a;
        if (root <= rayTmin || rayTmax <= root) {
            root = (h + sqrtd) / a;
            if (root <= rayTmin || rayTmax <= root)
                return false;
        }

        hit.t = root;
        hit.origin = ray.At(hit.t);
        Vector3 outwardNormal = (hit.origin - m_origin) / m_radius;
        hit.SetFaceNormal(ray, outwardNormal);
        hit.material = m_material;

        return true;
    }

    bool BoundingBox(AABB &outputBox) const override {
        outputBox = AABB(m_origin - Vector3(m_radius), m_origin + Vector3(m_radius));
        return true;
    }

private:
    Vector3 m_origin;
    float m_radius;
    std::shared_ptr<Material> m_material;
};
