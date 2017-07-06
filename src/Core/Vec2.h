/*!
  boldtemple Gaming ©, http://gaming.boldtemple.net
  OpenSource Project - Check Development, License & Readme Sections.

  BGE - boldtemple Cross Platform Game Engine
  /Core/Vec2.h
!*/

#ifndef VEC2_H_
#define VEC2_H_

#include <cmath>

class Vec2 {
public:
    constexpr static float PI_F = 3.14159265358979f;
    constexpr static float GRADUS = PI_F / 180.0f;
    constexpr static float RADIAN = 180.0f / PI_F;

    const static Vec2 ZERO;
    const static Vec2 UP;
    const static Vec2 DOWN;
    const static Vec2 LEFT;
    const static Vec2 RIGHT;

    Vec2();
    Vec2(const float& x, const float& y);

    float x, y;

    float GetLength() const;
    float GetSqrLength() const;
    float Dot(const Vec2& right) const;
    float GetAngle() const;
    Vec2 GetNormalized() const;
    Vec2 GetRotated(const float &angle) const;

    bool EqualTo(const Vec2& right) const;

    void Rotate(const float &angle);
    void Normalize();

    Vec2& operator=(const Vec2& right);
    bool operator==(const Vec2& right) const;

    friend const Vec2 operator+(const Vec2& left, const Vec2& right);
    friend const Vec2 operator-(const Vec2& left, const Vec2& right);
    friend const Vec2 operator*(const Vec2& left, const Vec2& right);
    friend const Vec2 operator*(const Vec2& left, const float& scale);

    Vec2& operator+=(const Vec2& right);
    Vec2& operator-=(const Vec2& right);
    Vec2& operator*=(const Vec2& right);
    Vec2& operator*=(const float& scale);

private:
    mutable bool _changed_length = true;
    mutable bool _changed_angle = true;

    mutable float _cache_length = false;
    mutable float _cache_angle = false;

    void SetCacheFlagTrue();
};

inline
Vec2::Vec2(): x(0.0f), y(0.0f){
}

inline
Vec2::Vec2(const float& x, const float& y) : x(x), y(y) {
}

inline
float Vec2::GetLength() const {
    if(_changed_length){
        _cache_length = sqrt(x * x + y * y);
        _changed_length ^= 1; // fast bool invert
    }
    return _cache_length;
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
float Vec2::GetAngle() const {
    if(_changed_angle){
        _cache_angle = atan2(this->y, this->x) * RADIAN;
        _changed_angle ^= 1; // fast bool invert
    }
    return _cache_angle;
}

inline
Vec2 Vec2::GetNormalized() const {
    float len = this->GetLength();
    return Vec2(this->x / len, this->y / len);
}

inline
Vec2 Vec2::GetRotated(const float& angle) const {
    float rad = angle * GRADUS;
    float sn = sin(rad);
    float cs = cos(rad);

    return Vec2((x * cs - y * sn), (x * sn + y * cs));
}

inline
bool Vec2::EqualTo(const Vec2& right) const{
    return *this == right;
}

inline
void Vec2::Rotate(const float &angle){
    float rad = angle * GRADUS;
    float sn = sin(rad);
    float cs = cos(rad);

    this->x = (x * cs - y * sn);
    this->y = (x * sn + y * cs);
}

inline
void Vec2::Normalize(){
    float len = this->GetLength();

    this->x /= len;
    this->y /= len;
}

inline
Vec2& Vec2::operator=(const Vec2& right) {
    //проверка на самоприсваивание
    if (this != &right) {
        this->x = right.x;
        this->y = right.y;
        SetCacheFlagTrue();
    }
    return *this;
}

inline
bool Vec2::operator==(const Vec2& right) const {
    return (this->x == right.x) && (this->y == right.y);
}

inline
void Vec2::SetCacheFlagTrue(){
       _changed_length = true;
       _changed_angle = true;
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
const Vec2 operator*(const Vec2& left, const Vec2& right) {
    return Vec2(left.x * right.x, left.y * right.y);
}

inline
const Vec2 operator*(const Vec2& left, const float& scale) {
    return Vec2(left.x * scale, left.y * scale);
}

inline
Vec2& Vec2::operator+=(const Vec2& right) {
    this->x += right.x;
    this->y += right.y;
    this->SetCacheFlagTrue();
    return *this;
}

inline
Vec2& Vec2::operator-=(const Vec2& right) {
    this->x -= right.x;
    this->y -= right.y;
    this->SetCacheFlagTrue();
    return *this;
}

inline
Vec2& Vec2::operator*=(const Vec2& right) {
    this->x *= right.x;
    this->y *= right.y;
    this->SetCacheFlagTrue();
    return *this;
}

inline
Vec2& Vec2::operator*=(const float& scale) {
    this->x *= scale;
    this->y *= scale;
    this->SetCacheFlagTrue();
    return *this;
}
#endif /* VEC2_H_ */
