//
// Created by Lucas on 15-05-2024.
//

#pragma once


#include <vector>
#include <algorithm>
#include "Object.h"

struct BVHNode : public Object {
    std::shared_ptr<Object> left;
    std::shared_ptr<Object> right;
    AABB box;

    BVHNode() = default;
    BVHNode(const std::vector<std::shared_ptr<Object>>& srcObjects) : BVHNode(srcObjects, 0, srcObjects.size()) {}

    BVHNode(const std::vector<std::shared_ptr<Object>>& srcObjects, int start, int end) {
        std::vector<std::shared_ptr<Object>> objects = srcObjects;

        int axis = RandomFloat(0, 2);
        auto comparator = (axis == 0) ? BoxXCompare : (axis == 1) ? BoxYCompare : BoxZCompare;

        int objectSpan = end - start;

        if (objectSpan == 1) {
            left = right = objects[start];
        } else if (objectSpan == 2) {
            if (comparator(objects[start], objects[start + 1])) {
                left = objects[start];
                right = objects[start + 1];
            } else {
                left = objects[start + 1];
                right = objects[start];
            }
        } else {
            std::sort(objects.begin() + start, objects.begin() + end, comparator);

            int mid = start + (objectSpan / 2);
            left = std::make_shared<BVHNode>(objects, start, mid);
            right = std::make_shared<BVHNode>(objects, mid, end);
        }

        AABB boxLeft, boxRight;

        if (!left->BoundingBox(boxLeft) || !right->BoundingBox(boxRight))
            std::cerr << "No bounding box in bvh node constructor." << std::endl;

        box = AABB::SurroundingBox(boxLeft, boxRight);
    }

    bool Hit(const Ray &ray, float rayTmin, float rayTmax, HitRecord &hit) const override {
        if (!box.Hit(ray, rayTmin, rayTmax))
            return false;

        bool hitLeft = left->Hit(ray, rayTmin, rayTmax, hit);
        bool hitRight = right->Hit(ray, rayTmin, hitLeft ? hit.t : rayTmax, hit);

        return hitLeft || hitRight;
    }

    bool BoundingBox(AABB &outputBox) const override {
        outputBox = box;
        return true;
    }

private:
    static inline bool BoxCompare(const std::shared_ptr<Object> a, const std::shared_ptr<Object> b, int axis) {
        AABB boxA;
        AABB boxB;

        if (!a->BoundingBox(boxA) || !b->BoundingBox(boxB))
            std::cerr << "No bounding box in bvh node constructor." << std::endl;

        return boxA.min[axis] < boxB.min[axis];
    }

    static inline bool BoxXCompare(const std::shared_ptr<Object> a, const std::shared_ptr<Object> b) {
        return BoxCompare(a, b, 0);
    }

    static inline bool BoxYCompare(const std::shared_ptr<Object> a, const std::shared_ptr<Object> b) {
        return BoxCompare(a, b, 1);
    }

    static inline bool BoxZCompare(const std::shared_ptr<Object> a, const std::shared_ptr<Object> b) {
        return BoxCompare(a, b, 2);
    }
};
