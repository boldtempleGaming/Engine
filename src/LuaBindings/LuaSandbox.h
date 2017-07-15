#ifndef LUASANDBOX_H
#define LUASANDBOX_H

#include <vector>

#include <sol.hpp>

#include "Core/Object.h"

#include "LuaBindings/LuaProxyObject.h"
#include "LuaBindings/LuaWindow.h"
#include "LuaBindings/LuaTimer.h"
#include "LuaBindings/LuaVec2.h"
#include "LuaBindings/LuaSprite.h"
#include "LuaBindings/LuaMouse.h"
#include "LuaBindings/LuaAudio.h"
#include "LuaBindings/LuaKeyboard.h"
#include "LuaBindings/LuaCamera.h"

class LuaSandbox
{
public:
    static void Init();

    static void AddScript(const std::string& origin, const std::string& script_lines);
    static void AddObject(const std::string& origin, const std::string& script_lines, Object *owner);

    static void EngineInit();
    static void EngineUpdate();
    static void EngineRender();
    static void EngineCleanUp();

private:
    static sol::state _lua;
    static sol::function  _fun_init;
    static sol::function  _fun_update;
    static sol::function  _fun_render;

    LuaSandbox();
};

#endif // LUASANDBOX_H
