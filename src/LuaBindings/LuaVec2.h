#ifndef LUAVEC2_H
#define LUAVEC2_H

#include <iomanip> // setprecision
#include <sstream> // stringstream

#include <sol.hpp>
#include <Core/Vec2.h>

namespace LuaVec2 {
    void bind(sol::state& lua);
}

#endif // LUAVEC2_H
