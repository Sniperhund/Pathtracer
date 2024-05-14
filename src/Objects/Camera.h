//
// Created by Lucas Täkker on 14/05/2024.
//

#pragma once

#include "../Math/Vector3.h"
#include "../Math/Ray.h"

class Camera {
public:
    Vector3 origin;
    float focalLength;

    Camera(Vector3 origin, float focalLength, float width, float height) {
        m_viewportHeight = 2.0f;
        m_viewportWidth = m_viewportHeight * (width / height);

        m_viewportU = Vector3(m_viewportWidth, 0, 0);
        m_viewportV = Vector3(0, -m_viewportHeight, 0);

        m_pixelDeltaU = m_viewportU / width;
        m_pixelDeltaV = m_viewportU / height;

        m_viewportUpperLeft = origin - Vector3(0, 0, focalLength) - m_viewportU/2 - m_viewportV/2;
        m_pixel00Loc = m_viewportUpperLeft + 0.5 * (m_pixelDeltaU + m_pixelDeltaV);
    }

    Ray GetRay(int x, int y) {
        Vector3 pixelCenter = m_pixel00Loc + ((float)x * m_pixelDeltaU) + ((float)y * m_pixelDeltaV);
        Vector3 rayDirection = pixelCenter - origin;
        return Ray(origin, rayDirection);
    }

private:
    float m_viewportHeight, m_viewportWidth;
    Vector3 m_viewportU, m_viewportV, m_pixelDeltaU, m_pixelDeltaV, m_viewportUpperLeft, m_pixel00Loc;
};
