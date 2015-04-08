/*
 * Entity.h
 *
 *  Created on: 23 июля 2014 г.
 *      Author: snickers
 */

#ifndef ENTITY_H_
#define ENTITY_H_

#include <string>
#include <vector>
#include <iostream>

#include <SDL2/SDL.h>

#include "Core/type_events.h"
#include "Core/Vec2.h"
#include "GUI/Window.h"
#include "Render/Surface.h"
#include "Render/Animation.h"
#include "Render/Camera.h"

enum entity_type {
    TYPE_STATIC = 0,
    TYPE_DYNAMIC
};

class Entity {
public:

    struct move_info {
        Entity* entity;
        SDL_Rect rect;
    };

    Entity();
    virtual ~Entity();

    static std::vector<Entity*> EntityList;

    SDL_Rect rect, anim_rect;
    Uint8 anim_state;

    virtual bool OnLoad(std::string fname, int width, int height,
            int max_frames);
    virtual void OnUpdate();
    virtual void OnCollide(Entity* ent);
    virtual void OnRender(const double& interpolation);
    virtual void OnCleanUp();

    void Move(const Vec2& pos);
    int GetType();

protected:
    SDL_Event event;
    move_info info;
    double angle;
    SDL_Texture* texture;
    Animation anim_control;

private:
    entity_type type = TYPE_STATIC;
};

#endif /* ENTITY_H_ */
