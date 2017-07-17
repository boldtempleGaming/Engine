#include "LuaDrawer.h"

void LuaDrawer::bind(sol::state& lua){
    lua.new_simple_usertype<Drawer>("Drawer",
        "line", &Drawer::Line,
        "rect", &Drawer::Rect,
        "circle", &Drawer::Circle
    );
}
