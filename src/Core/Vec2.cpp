/*
 * Vec2.cpp
 *
 *  Created on: 25 авг. 2014 г.
 *      Author: snickers
 */

#include "Vec2.h"

Vec2::Vec2() : x(0), y(0) {}

Vec2::Vec2(const float& x, const float& y) : x(x), y(y) {}

float Vec2::GetLength() const {
	return sqrt(x * x + y * y);
}

Vec2 Vec2::GetNormalized() const{
	float len = this->GetLength();
	return Vec2( (float)this->x / len, (float)this->y / len);
}

Vec2 Vec2::GetRotated(const double& angle) const {
	float rad = (angle) * GRADUS;
	float sn = sin(rad);
	float cs = cos(rad);
	return Vec2((x * cs - y * sn), (x * sn + y * cs));
}

Vec2& Vec2::operator=(const Vec2& right) {
	//проверка на самоприсваивание
	if (this != &right) {
		this->x = right.x;
		this->y = right.y;
	}
	return *this;
}

bool Vec2::operator == (const Vec2& right) const {
    return (this->x == right.x) && (this->y == right.y);
}

const Vec2 operator+(const Vec2& left, const Vec2& right) {
	return Vec2(left.x + right.x, left.y + right.y);
}

const Vec2 operator-(const Vec2& left, const Vec2& right) {
	return Vec2(left.x - right.x, left.y - right.y);
}

const Vec2 operator*(const Vec2& left, const float& scale) {
	return Vec2(left.x * scale, left.y * scale);
}

float operator*(const Vec2& left, const Vec2& right){
	return left.x * right.x + left.y  * right.y;
}

Vec2& operator+=(Vec2& left, const Vec2& right) {
	left.x += right.x;
	left.y += right.y;
	return left;
}

Vec2& operator-=(Vec2& left, const Vec2& right) {
	left.x -= right.x;
	left.y -= right.y;
	return left;
}

Vec2& operator*=(Vec2& left, const Vec2& right) {
	left.x *= right.x;
	left.y *= right.y;
	return left;
}

Vec2& operator*=(Vec2& left, const float& scale) {
	left.x *= scale;
	left.y *= scale;
	return left;
}
