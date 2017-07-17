#ifndef LUADRAWER_H
#define LUADRAWER_H

#include <sol.hpp>
#include "Render/Drawer.h"

namespace LuaDrawer {
    void bind(sol::state& lua);
}

#endif // LUADRAWER_H
