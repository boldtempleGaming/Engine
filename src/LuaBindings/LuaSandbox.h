#ifndef LUASANDBOX_H
#define LUASANDBOX_H

#include <vector>

#include <sol.hpp>

#include <LuaBindings/LuaVec2.h>
#include <LuaBindings/LuaSprite.h>
#include <LuaBindings/LuaMouse.h>

class LuaSandbox
{
public:
    LuaSandbox();

    void AddScript(const std::string& origin, const std::string& script_lines);

    void EngineInit();
    void EngineUpdate();
    void EngineRender();
    void EngineCleanUp();

private:
    sol::state _lua;
    std::vector<sol::table> _Scripts;
};

#endif // LUASANDBOX_H
