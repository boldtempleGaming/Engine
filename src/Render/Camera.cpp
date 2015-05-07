/*
 * Camera.cpp
 *
 *  Created on: 26 июля 2014 г.
 *      Author: snickers
 */

#include "Camera.h"

Camera::Camera(const Vec2& pos, const Vec2& viewport) :
        _pos(pos), _viewport(viewport) {
}

void Camera::SetPos(const Vec2& pos) {
    _pos = pos;
}

void Camera::SetViewport(const Vec2& viewport) {
    _viewport = viewport;
}

bool Camera::InView(SDL_Rect* rect) const {
    return (rect->x >= _pos.x - rect->w) &&
           (rect->x <= _viewport.x + rect->w) &&
           (rect->y >= _pos.y - rect->h) &&
           (rect->y <= _viewport.y + rect->h);
}

bool Camera::InView(int x, int y, int h, int w) const {
    return (x >= _pos.x - w) &&
           (x <= _viewport.x + w) &&
           (y >= _pos.y -h) &&
           (y <= _viewport.y + h);
}

bool Camera::InView(const Vec2& pos, const Vec2& size) const {
    return (pos.x >= _pos.x - size.x) &&
           (pos.x <= _viewport.x + -size.x) &&
           (pos.y >= _pos.y - size.y) &&
           (pos.y <= _viewport.y + size.y);
}

void Camera::Move(const Vec2& delta_pos) {
    _pos += delta_pos;
}

int Camera::X() const {
    return _pos.x;
}

int Camera::Y() const {
    return _pos.y;
}

int Camera::W() const {
    return _viewport.x;
}

int Camera::H() const {
    return _viewport.y;
}
