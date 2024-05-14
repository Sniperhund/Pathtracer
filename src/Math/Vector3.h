//
// Created by Lucas Täkker on 14/05/2024.
//

#pragma once

#include <cmath>
#include "Utility.h"

class Vector3 {
public:
    float x = 0, y = 0, z = 0;

    Vector3() {
        x = y = z = 0;
    }
    Vector3(float t) {
        x = y = z = t;
    }
    Vector3(Vector3 const &v) {
        x = v.x;
        y = v.y;
        z = v.z;
    }
    Vector3(float x, float y, float z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    Vector3& operator+=(const Vector3& v) {
        this->x += v.x;
        this->y += v.y;
        this->z += v.z;
        return *this;
    }
    Vector3& operator+=(float t) {
        this->x += t;
        this->y += t;
        this->z += t;
        return *this;
    }

    Vector3& operator-=(const Vector3& v) {
        this->x -= v.x;
        this->y -= v.y;
        this->z -= v.z;
        return *this;
    }
    Vector3& operator-=(float t) {
        this->x -= t;
        this->y -= t;
        this->z -= t;
        return *this;
    }

    Vector3& operator/=(const Vector3& v) {
        this->x /= v.x;
        this->y /= v.y;
        this->z /= v.z;
        return *this;
    }
    Vector3& operator/=(float t) {
        this->x /= t;
        this->y /= t;
        this->z /= t;
        return *this;
    }

    Vector3& operator*=(const Vector3& v) {
        this->x *= v.x;
        this->y *= v.y;
        this->z *= v.z;
        return *this;
    }
    Vector3& operator*=(float t) {
        this->x *= t;
        this->y *= t;
        this->z *= t;
        return *this;
    }

    float Length() const {
        return sqrt(Squared());
    }

    float Squared() const {
        return x * x + y * y + z * z;
    }

    bool NearZero() const {
        float s = 1e-8;
        return (fabsf(x) < s) && (fabsf(y) < s) && (fabsf(z) < s);
    }

    static Vector3 Random() {
        return Vector3(RandomFloat(), RandomFloat(), RandomFloat());
    }

    static Vector3 Random(float min, float max) {
        return Vector3(RandomFloat(min, max), RandomFloat(min, max), RandomFloat(min, max));
    }
};

inline std::ostream& operator<<(std::ostream& out, const Vector3& v) {
    return out << v.x << ' ' << v.y << ' ' << v.z;
}

inline Vector3 operator+(const Vector3& v, const Vector3& t) {
    return Vector3(v.x + t.x, v.y + t.y, v.z + t.z);
}

inline Vector3 operator+(const Vector3& v, float t) {
    return Vector3(v.x + t, v.y + t, v.z + t);
}
inline Vector3 operator+(float t, const Vector3& v) { return Vector3(v + t); }

inline Vector3 operator-(const Vector3& v, const Vector3& t) {
    return Vector3(v.x - t.x, v.y - t.y, v.z - t.z);
}

inline Vector3 operator-(const Vector3& v, float t) {
    return Vector3(v.x - t, v.y - t, v.z - t);
}
inline Vector3 operator-(float t, const Vector3& v) { return Vector3(v - t); }

inline Vector3 operator/(const Vector3& v, const Vector3& t) {
    return Vector3(v.x / t.x, v.y / t.y, v.z / t.z);
}

inline Vector3 operator/(const Vector3& v, float t) {
    return Vector3(v.x / t, v.y / t, v.z / t);
}
inline Vector3 operator/(float t, const Vector3& v) { return Vector3(v / t); }

inline Vector3 operator*(const Vector3& v, const Vector3& t) {
    return Vector3(v.x * t.x, v.y * t.y, v.z * t.z);
}

inline Vector3 operator*(const Vector3& v, float t) {
    return Vector3(v.x * t, v.y * t, v.z * t);
}
inline Vector3 operator*(float t, const Vector3& v) { return Vector3(v * t); }

inline Vector3 operator-(const Vector3& v) {
    return Vector3(-v.x, -v.y, -v.z);
}

inline float Dot(const Vector3& v, const Vector3& t) {
    return v.x * t.x + v.y * t.y + v.z * t.z;
}

inline Vector3 Cross(const Vector3& v, const Vector3& t) {
    return Vector3(v.y * t.z - v.z * t.y,
                   v.z * t.x - v.x * t.z,
                   v.x * t.y - v.y * t.x);
}

inline Vector3 Normalize(const Vector3& v) {
    return v / v.Length();
}

inline Vector3 RandomInNormalizedSphere() {
    while (true) {
        Vector3 p = Vector3::Random(-1, 1);
        if (p.Squared() < 1)
            return p;
    }
}

inline Vector3 RandomNormalizedVector() {
    return Normalize(RandomInNormalizedSphere());
}

inline Vector3 RandomOnHemisphere(const Vector3& normal) {
    Vector3 onNormalizedSphere = RandomNormalizedVector();
    if (Dot(onNormalizedSphere, normal) > 0.0f)
        return onNormalizedSphere;
    else
        return -onNormalizedSphere;
}

inline Vector3 RandomInUnitDisk() {
    while (true) {
        Vector3 p = Vector3(RandomFloat(-1, 1), RandomFloat(-1, 1), 0);
        if (p.Squared() < 1)
            return p;
    }
}

inline Vector3 Reflect(const Vector3& v, const Vector3& t) {
    return v - 2 * Dot(v, t) * t;
}

inline Vector3 Refract(const Vector3& uv, const Vector3& v, float etaiOverEtat) {
    float cosTheta = fmin(Dot(-uv, v), 1.0f);
    Vector3 rOutPerp = etaiOverEtat * (uv + cosTheta * v);
    Vector3 rOutParallel = -sqrt(fabsf(1.0f - rOutPerp.Squared())) * v;
    return rOutPerp + rOutParallel;
}