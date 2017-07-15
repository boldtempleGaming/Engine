#ifndef LUACAMERA_H
#define LUACAMERA_H

#include <sol.hpp>
#include "Render/Camera.h"

namespace LuaCamera {
    void bind(sol::state& lua);
}

#endif // LUACAMERA_H
