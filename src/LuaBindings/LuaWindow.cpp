#include "LuaWindow.h"

void LuaWindow::bind(sol::state& lua){
    lua.new_simple_usertype<Engine_Color>(
        "Color",
        sol::constructors<sol::types<>,
                          sol::types<Uint8, Uint8, Uint8, Uint8>,
                          sol::types<SDL_Color&>
                         >(),
        "r", &SDL_Color::r,
        "g", &SDL_Color::g,
        "b", &SDL_Color::b,
        "a", &SDL_Color::a);

    lua.new_simple_usertype<Window>("Window",
        "getCamera", &Window::GetCamera,
        "getSize", &Window::GetSize,
        "getBackgroundColor", &Window::GetBackgroundColor,
        "setBackgroundColor", &Window::SetBackgroundColor,
        "setSize", &Window::SetSize,
        "setMode", &Window::SetMode,
        "isFullscreen",  &Window::IsFullscreen
    );
}
