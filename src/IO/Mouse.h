/*!
 boldtemple Gaming ©, http://gaming.boldtemple.net
 OpenSource Project - Check Development, License & Readme Sections.

 BGE - boldtemple Cross Platform Game Engine
 IO/Mouse.h
 !*/

#ifndef MOUSE_H
#define	MOUSE_H

#include <iostream>

#include <SDL2/SDL.h>

#include "Core/Vec2.h"
#include "GUI/Window.h"

#include "Engine.h"

enum mouse_button {
    MOUSE_LEFT = 1,
    MOUSE_MIDDLE,
    MOUSE_RIGHT
};

enum mouse_wheel {
    MOUSE_WHEEL_UP = 1,
    MOUSE_WHEEL_DOWN
};

class Object;
class Engine;
class Mouse {
public:
    static void SetPos(const Vec2& pos);
    static void SetCapture(bool capture);

    static Vec2 GetPos();
    static void GetPos(int* x, int* y);
    static Vec2 GetWheel();
    static void GetWheel(int* x, int* y);
    
    static bool Intersect(const Vec2 &pos, const Vec2& size);
    static bool Intersect(Object* object);

    static bool Captured();
    static bool InWindow();
    
    static bool Pressed(mouse_button m_btn);
    static bool Wheeled(mouse_wheel m_whl);
    
    static bool AnyPressed();
    static bool AnyWheeled();
    
    

private:
    Mouse();
    friend Engine;
    static int _wheel_x, _wheel_y;
    static void SetWheel(const int& x, const int& y);
    static void ResetWheel();
};

inline
void Mouse::SetPos(const Vec2& pos) {
    if (Window::GetWindow() != nullptr) {
        SDL_WarpMouseInWindow(Window::GetWindow(), pos.x, pos.y);
    }
}

inline
void Mouse::SetCapture(bool capture) {
    if (SDL_SetRelativeMouseMode(capture ? SDL_TRUE : SDL_FALSE) < 0) {
        std::cerr << SDL_GetError() << std::endl;
    }
}

inline
Vec2 Mouse::GetPos() {
    static int x, y;
    SDL_GetMouseState(&x, &y);
    return Vec2(x, y);
}

inline
void Mouse::GetPos(int* x, int* y) {
    SDL_GetMouseState(x, y);
}

inline
Vec2 Mouse::GetWheel(){
    return Vec2(_wheel_x, _wheel_y);
}

inline
void Mouse::GetWheel(int* x, int* y){
    if(x != nullptr){
        *x = _wheel_x;
    }
    if(y != nullptr){
        *y = _wheel_y;
    }
}

inline
bool Mouse::Intersect(const Vec2& pos, const Vec2 &size){
    Vec2 mouse_pos = GetPos() + Window::GetCamera()->GetPos();
    if(mouse_pos.x < pos.x || mouse_pos.x > pos.x + size.x) return false;
    if(mouse_pos.y < pos.y || mouse_pos.y > pos.y + size.y) return false;
    return true;
}

inline
bool Mouse::Intersect(Object* object){
    return Intersect(object->GetGlobalPos(), object->GetSize());
}

inline
bool Mouse::Captured() {
    return (SDL_GetRelativeMouseMode() == SDL_TRUE ? true : false);
}

inline
bool Mouse::InWindow() {
    return (Window::GetWindow() == SDL_GetMouseFocus());
}

inline
bool Mouse::Pressed(mouse_button m_btn) {
    Uint8 state = SDL_GetMouseState(nullptr, nullptr);
    return (state & SDL_BUTTON(static_cast<int> (m_btn)));
}

inline
bool Mouse::Wheeled(mouse_wheel m_whl){
    switch(m_whl){
        case MOUSE_WHEEL_UP:
            if(_wheel_y > 0) return true;
            break;
        case MOUSE_WHEEL_DOWN:
            if(_wheel_y < 0) return true;
            break;
    }
    
    return false;
}

inline
bool Mouse::AnyPressed() {
    return (SDL_GetMouseState(nullptr, nullptr) != 0);
}

inline
bool Mouse::AnyWheeled() {
    return (_wheel_x != 0 || _wheel_y != 0);
}
#endif	/* MOUSE_H */

