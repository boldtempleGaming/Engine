#ifndef LUAMOUSE_H
#define LUAMOUSE_H

#include <sol.hpp>
#include "IO/Mouse.h"

namespace LuaMouse {
    void bind(sol::state& lua);
}

#endif // LUAMOUSE_H
