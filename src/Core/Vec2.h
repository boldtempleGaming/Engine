#ifndef VEC2_H_
#define VEC2_H_

#include <cmath>
const static float GRADUS = 3.14159265359f / 180;

class Vec2 {
public:
    Vec2();
    Vec2(const float& x, const float& y);

    float x, y;
    float GetLength() const;

    Vec2 GetNormalized() const;
    Vec2 GetRotated(const double& angle) const;

    const float& Dot(const Vec2& right);

    Vec2& operator=(const Vec2& right);
    bool operator==(const Vec2& right) const;

    friend const Vec2 operator+(const Vec2& left, const Vec2& right);
    friend const Vec2 operator-(const Vec2& left, const Vec2& right);
    friend const Vec2 operator*(const Vec2& left, const float& scale);
    friend float operator*(const Vec2& left, const Vec2& right);
    friend Vec2& operator+=(Vec2& left, const Vec2& right);
    friend Vec2& operator-=(Vec2& left, const Vec2& right);
    friend Vec2& operator*=(Vec2& left, const float& scale);
};

#endif /* VEC2_H_ */
