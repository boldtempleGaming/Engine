/*!
  boldtemple Gaming ©, http://gaming.boldtemple.net
  OpenSource Project - Check Development, License & Readme Sections.

  BGE - boldtemple Cross Platform Game Engine
  /Core/Vec2.h
!*/

#ifndef VEC2_H_
#define VEC2_H_

#include <cmath>

const static float PI_F = 3.14159265358979f;
const static float GRADUS = PI_F / 180.0f;

class Vec2 {
public:
    const static Vec2 Zero;
    const static Vec2 Up;
    const static Vec2 Down;
    const static Vec2 Left;
    const static Vec2 Right;

    Vec2();
    Vec2(const float& x, const float& y);

    float x, y;

    float GetLength() const;
    float GetSqrLength() const;
    float Dot(const Vec2& right) const;
    Vec2 GetNormalized() const;
    Vec2 GetRotated(const double& angle) const;

    Vec2& operator=(const Vec2& right);
    bool operator==(const Vec2& right) const;

    friend const Vec2 operator+(const Vec2& left, const Vec2& right);
    friend const Vec2 operator-(const Vec2& left, const Vec2& right);
    friend const Vec2 operator*(const Vec2& left, const float& scale);
    //friend float operator*(const Vec2& left, const Vec2& right);
    friend Vec2& operator+=(Vec2& left, const Vec2& right);
    friend Vec2& operator-=(Vec2& left, const Vec2& right);
    friend Vec2& operator*=(Vec2& left, const float& scale);
};

inline
Vec2::Vec2() : x(0), y(0) {
}

inline
Vec2::Vec2(const float& x, const float& y) : x(x), y(y) {
}

inline
float Vec2::GetLength() const {
    return sqrt(x * x + y * y);
}

inline
float Vec2::GetSqrLength() const {
    return (x * x + y * y);
}

inline
float Vec2::Dot(const Vec2& right) const{
    return (this->x * right.x) + (this->y * right.y);
}

inline
Vec2 Vec2::GetNormalized() const {
    float len = this->GetLength();
    return Vec2(this->x / len, this->y / len);
}

inline
Vec2 Vec2::GetRotated(const double& angle) const {
    float rad = (angle) * GRADUS;
    float sn = sin(rad);
    float cs = cos(rad);
    return Vec2((x * cs - y * sn), (x * sn + y * cs));
}

inline
Vec2& Vec2::operator=(const Vec2& right) {
    //проверка на самоприсваивание
    if (this != &right) {
        this->x = right.x;
        this->y = right.y;
    }
    return *this;
}

inline
bool Vec2::operator==(const Vec2& right) const {
    return (this->x == right.x) && (this->y == right.y);
}

inline
const Vec2 operator+(const Vec2& left, const Vec2& right) {
    return Vec2(left.x + right.x, left.y + right.y);
}

inline
const Vec2 operator-(const Vec2& left, const Vec2& right) {
    return Vec2(left.x - right.x, left.y - right.y);
}

inline
const Vec2 operator*(const Vec2& left, const float& scale) {
    return Vec2(left.x * scale, left.y * scale);
}

//inline
//float operator*(const Vec2& left, const Vec2& right) {
//    return left.x * right.x + left.y * right.y;
//}

inline
Vec2& operator+=(Vec2& left, const Vec2& right) {
    left.x += right.x;
    left.y += right.y;
    return left;
}

inline
Vec2& operator-=(Vec2& left, const Vec2& right) {
    left.x -= right.x;
    left.y -= right.y;
    return left;
}

inline
Vec2& operator*=(Vec2& left, const float& scale) {
    left.x *= scale;
    left.y *= scale;
    return left;
}

#endif /* VEC2_H_ */
