#include "LuaSandbox.h"

LuaSandbox::LuaSandbox(){
    _lua.open_libraries(sol::lib::base, sol::lib::package, sol::lib::math);

    LuaSprite::bind(_lua);
    LuaMouse::bind(_lua);
    LuaVec2::bind(_lua);

    _lua.script(R"(
               count = 0;
               ScriptsArray = {}

               function push_script()
                 print(Script)
                 count = count + 1
                 ScriptsArray[count] = Script
               end

               local update_env = {
                         print = print,
                         math = math,
                         require = require,
                         Sprite = Sprite,
                         Animation = Animation,
                         Vec2 = Vec2,
                         Mouse = Mouse,
                         MouseWheel = MouseWheel,
                         MouseButton = MouseButton
                         } -- add functions you know are safe here

               -- run code under environment [Lua 5.2]
               function run(untrusted_code)
                -- make environment
                local env = update_env
                update_env.Script = Script

                 local untrusted_function = load(untrusted_code, nil, 't', env), message
                 if not untrusted_function then return nil, message end
                 return pcall(untrusted_function)
               end

               function init()
                    for i = 1, #ScriptsArray do
                       ScriptsArray[i]:Init(update_env)
                    end
               end

               function update()
                    for i = 1, #ScriptsArray do
                       ScriptsArray[i]:Update(update_env)
                    end
               end

               function render()
                    for i = 1, #ScriptsArray do
                        ScriptsArray[i]:Render(update_env)
                    end
               end

               )");
}

void LuaSandbox::AddScript(const std::string& origin, const std::string& script_lines){
    sol::table table = _lua.create_named_table("Script");

    try{
        _lua["run"](script_lines);
        _lua["push_script"]();
    }catch(sol::error ex){
        std::cerr << "Error at file: \"" << origin << "\"" << std::endl;
        std::cerr << ex.what() << std::endl;
    }
}

void LuaSandbox::EngineInit(){
    _lua["init"]();
}

void LuaSandbox::EngineUpdate(){
    _lua["update"]();
}

void LuaSandbox::EngineRender(){
    _lua["render"]();
}

void LuaSandbox::EngineCleanUp(){

}
