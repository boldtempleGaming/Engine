/*
 * Entity.cpp
 *
 *  Created on: 23 июля 2014 г.
 *      Author: snickers
 */

#include "Entity.h"

std::vector<Entity*> Entity::EntityList;

Entity::Entity() {
    texture = nullptr;
    angle = 0;
    rect = {0,0,0,0};
    anim_state = 0;
    anim_rect = rect;

    SDL_zero(event);
    event.type = EVENT_MOVE;

    Move(Vec2(0.0f,0.0f));
    EntityList.push_back(this);
}

Entity::~Entity() {
}

bool Entity::OnLoad(std::string fname, int width, int height,
        int max_frames) {
    texture = Surface::LoadTexture(fname);

    rect.w = width;
    rect.h = height;

    anim_rect = rect;

    anim_control.SetMaxFrame(max_frames);
    return true;
}

void Entity::OnUpdate() {
    anim_control.OnAnimation();
}

void Entity::OnCollide(Entity* ent){
    
}

void Entity::OnRender(const double& interpolation) {

    SDL_Rect tmpRect = {rect.x + Camera::X(), rect.y + Camera::Y(), rect.w,
        rect.h};
    if (Camera::InView(&tmpRect)) {
        anim_rect.x = anim_rect.w * anim_control.GetCurrentFrame();
        if (this->anim_control.GetMaxFrame() > 0) {
            Surface::Draw(texture, &anim_rect, &tmpRect);
        } else {
            Surface::Draw(texture, &tmpRect);
        }
    }

}

void Entity::Move(const Vec2& pos) {
    rect.x = pos.x;
    rect.y = pos.y;
    info = {this, rect};
    event.user.data1 = &info;
    SDL_PushEvent(&event);
}

int Entity::GetType(){
    return type;
}

void Entity::OnCleanUp() {
    for (auto it = EntityList.begin(); it != EntityList.end(); it++) {
        if (*it == this) {
            EntityList.erase(it);
            //TODO Memory leak on entity clean up?
            break;
        }
    }
}
