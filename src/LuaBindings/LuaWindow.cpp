#include "LuaWindow.h"

void LuaWindow::bind(sol::state& lua){
    lua.new_simple_usertype<Window>("Window",// sol::constructors<>(),
        "getCamera", &Window::GetCamera,
        "getSize", sol::resolve<Vec2 ()>(&Window::GetSize),
        "setSize", sol::resolve<void (const Vec2&)>(&Window::SetSize),
        "setMode", &Window::SetMode,
        "isFullscreen",  sol::resolve<bool ()>(&Window::IsFullscreen)
    );
}
