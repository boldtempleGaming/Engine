#include "LuaMouse.h"

void LuaMouse::bind(sol::state& lua){

    lua.new_enum("MouseButton",
                 "LEFT", MOUSE_LEFT,
                 "MIDDLE", MOUSE_MIDDLE,
                 "RIGHT", MOUSE_RIGHT
    );

    lua.new_enum("MouseWheel",
                 "WHEEL_UP", MOUSE_WHEEL_UP,
                 "WHEEL_DOWN", MOUSE_WHEEL_DOWN
    );

    lua.new_simple_usertype<Mouse>("Mouse",
        "setCapture", &Mouse::SetCapture,
        "getPos", sol::resolve(static_cast<Vec2 (*)(void)>(&Mouse::GetPos)),
        "setPos", sol::resolve(static_cast<void (*)(const Vec2&)>(&Mouse::SetPos)),
        "captured", &Mouse::Captured,
        "inWindow", &Mouse::InWindow,
        "anyPressed", &Mouse::AnyPressed,
        "anyWheeled", &Mouse::AnyWheeled
    );
}
