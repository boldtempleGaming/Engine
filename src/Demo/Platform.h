//
// Created by winpooh on 28.07.15.
//

#ifndef ENGINE_PLATFORM_H
#define ENGINE_PLATFORM_H

#include "Core/Object.h"
#include "Render/Sprite.h"
#include <Core/Resources.h>
#include <Core/Collider.h>

class Platform: public Object {
public:
    Platform(const Vec2& pos, const Vec2& size);
    void OnUpdate();
    void OnRender();

private:
    Sprite _sprite;
};


#endif //ENGINE_PLATFORM_H
