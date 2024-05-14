//
// Created by Lucas on 14-05-2024.
//

#pragma once

#include <vector>
#include <memory>

#include "Object.h"

class Scene {
public:
    void AddObject(std::shared_ptr<Object> object) {
        m_objects.push_back(object);
    }

    bool Hit(const Ray& ray, float rayTmin, float rayTmax, HitRecord& hit) const {
        HitRecord tempHit;
        bool hitAnything = false;
        float closestSoFar = rayTmax;

        for (std::shared_ptr<Object> object : m_objects) {
            if (object->Hit(ray, rayTmin, closestSoFar, tempHit)) {
                hitAnything = true;
                closestSoFar = tempHit.t;
                hit = tempHit;
            }
        }

        return hitAnything;
    }

private:
    std::vector<std::shared_ptr<Object>> m_objects;
};
