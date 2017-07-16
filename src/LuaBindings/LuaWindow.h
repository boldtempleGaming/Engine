#ifndef LUAWINDOW_H
#define LUAWINDOW_H

#include <sol.hpp>
#include <SDL2/SDL.h>

#include "GUI/Window.h"

namespace LuaWindow {
    struct Engine_Color: public SDL_Color{
        Engine_Color()
        {}

        Engine_Color(SDL_Color& orig):
            SDL_Color(orig)
        {}

        Engine_Color(Uint8 r, Uint8 g, Uint8 b, Uint8 a){
            this->r = r;
            this->g = g;
            this->b = b;
            this->a = a;
        }
    };

    void bind(sol::state& lua);
}

#endif // LUAWINDOW_H
