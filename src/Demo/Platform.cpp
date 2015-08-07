//
// Created by winpooh on 28.07.15.
//

#include <Core/Resources.h>
#include <Core/Collider.h>
#include "Platform.h"

Platform::Platform(const Vec2& pos, const Vec2& size){
    SetPos(pos);
    SetSize(size);
    _sprite.SetFrameSize(size);
    _sprite.SetTexture(Resources::GetTexture("grassMid.png"));

    Collider::RegisterObject(this, Vec2(), size, true);

    SetType(OBJ_GROUND);
}

void Platform::OnUpdate() {

}

void Platform::OnRender() {
    Vec2 rect_pos = GetGlobalPos();
    Collider* col = Collider::GetCollider(this);

    SDL_Rect _draw_rect = {rect_pos.x + col->_offset.x, rect_pos.y + col->_offset.y, col->_size.x, col->_size.y};

    //if(Surface::GetInterpolation() > 0)
    //std::cout << Surface::GetInterpolation() << std::endl;

    _sprite.Draw(GetGlobalPos(), GetSize(), Window::GetCamera());

    SDL_SetRenderDrawColor(Window::GetRenderer(), 255, 255, 0, 255);
    SDL_RenderDrawRect(Window::GetRenderer(), &_draw_rect);
    SDL_SetRenderDrawColor(Window::GetRenderer(), BACKGROUND_COLOR.r, BACKGROUND_COLOR.g, BACKGROUND_COLOR.b, 255);

}
