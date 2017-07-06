#include "Camera.h"

Camera::Camera(const Vec2& pos, const Vec2& viewport) :
        _pos(pos), _viewport(viewport) {
}

void Camera::SetPos(const Vec2& pos) {
    _pos = pos;
}

void Camera::SetViewport(const Vec2& viewport, const Vec2& offset) {
    _viewport = viewport;
    _offset = offset;
}

bool Camera::InView(SDL_Rect* rect) const {
    if(_pos.x >= rect->x + rect->w || _pos.x + _viewport.x <= rect->x) return false;
    if(_pos.y >= rect->y + rect->h || _pos.y + _viewport.y <= rect->y) return false;
    return true;
}

bool Camera::InView(int x, int y, int h, int w) const {
    if(_pos.x >= x + w || _pos.x + _viewport.x <= x) return false;
    if(_pos.y >= y + h || _pos.y + _viewport.y <= y) return false;
    return true;
}

bool Camera::InView(const Vec2& pos, const Vec2& size) const {
    if(_pos.x >= pos.x + size.x || _pos.x + _viewport.x <= pos.x) return false;
    if(_pos.y >= pos.y + size.y || _pos.y + _viewport.y <= pos.y) return false;
    return true;
}

void Camera::Move(const Vec2& delta_pos) {
    _pos += delta_pos;
}

Vec2 Camera::GetPos() const{
    return _pos - _offset;
}

Vec2 Camera::GetViewport() const{
    return _viewport;
}

int Camera::X() const {
    return GetPos().x;
}

int Camera::Y() const {
    return GetPos().y;
}

int Camera::W() const {
    return _viewport.x;
}

int Camera::H() const {
    return _viewport.y;
}
