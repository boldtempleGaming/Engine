#ifndef LUAWINDOW_H
#define LUAWINDOW_H

#include <sol.hpp>
#include <GUI/Window.h>

namespace LuaWindow {
    void bind(sol::state& lua);
}

#endif // LUAWINDOW_H
