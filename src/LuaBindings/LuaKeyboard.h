#ifndef LUAKEYBOARD_H
#define LUAKEYBOARD_H

#include <sol.hpp>
#include "IO/Keyboard.h"

namespace LuaKeyboard {
    void bind(sol::state& lua);
}

#endif // LUAKEYBOARD_H
