#ifndef LUASPRITE_H
#define LUASPRITE_H

#include <sol.hpp>
#include "Render/Sprite.h"

namespace LuaSprite {
    void bind(sol::state& lua);
}

#endif // LUASPRITE_H
