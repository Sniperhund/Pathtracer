//
// Created by Lucas on 14-05-2024.
//

#pragma once

#include <vector>
#include <memory>

#include "Object.h"
#include "BVHNode.h"

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

    bool BoundingBox(AABB& outputBox) const {
        if (m_objects.empty()) return false;

        AABB tempBox;
        bool firstBox = true;

        for (std::shared_ptr<Object> object : m_objects) {
            if (!object->BoundingBox(tempBox)) return false;
            outputBox = firstBox ? tempBox : AABB::SurroundingBox(outputBox, tempBox);
            firstBox = false;
        }

        return true;
    }

    void BuildBVH() {
        std::shared_ptr<BVHNode> bvhTree = std::make_shared<BVHNode>(m_objects);
        m_objects.clear();
        m_objects.push_back(bvhTree);
    }

private:
    std::vector<std::shared_ptr<Object>> m_objects;
};
