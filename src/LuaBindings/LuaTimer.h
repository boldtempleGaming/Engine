#ifndef LUATIMER_H
#define LUATIMER_H

#include <sol.hpp>
#include "Core/Timer.h"

namespace LuaTimer {
    void bind(sol::state& lua);
}

#endif // LUATIMER_H
