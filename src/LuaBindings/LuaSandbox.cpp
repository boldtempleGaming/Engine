#include "LuaSandbox.h"

sol::state     LuaSandbox::_lua;
sol::function  LuaSandbox::_fun_init;
sol::function  LuaSandbox::_fun_update;
sol::function  LuaSandbox::_fun_render;

LuaSandbox::LuaSandbox(){}

void LuaSandbox::Init(){
    _lua.open_libraries(sol::lib::base,
                        sol::lib::package,
                        sol::lib::math,
                        sol::lib::table);

    LuaProxyObject::bind(_lua);
    LuaWindow::bind(_lua);
    LuaTimer::bind(_lua);
    LuaSprite::bind(_lua);
    LuaMouse::bind(_lua);
    LuaVec2::bind(_lua);
    LuaAudio::bind(_lua);
    LuaKeyboard::bind(_lua);
    LuaCamera::bind(_lua);


    _lua.script(R"(
               package.path = "./../Data/?.lua"
               count = 0
               ScriptsArray = {}
               ObjectsArray = {}

               function push_script()
                    count = count + 1
                    table.insert(ScriptsArray, count, Script)
               end

                function push_object(id)
                    ObjectsArray[id] = Object
                end

                function remove_object(id)
                     ObjectsArray[id] = nil
                end

                -- run code under environment [Lua 5.2]
               function run(untrusted_code, run_object)
                -- make environment
                -- add functions you know are safe here
                local env = {
                          print = print,
                          math = math,
                          table = table,
                          pcall = pcall,
                          require = require,
                          Sprite = Sprite,
                          Flip = Flip,
                          Animation = Animation,
                          Vec2 = Vec2,
                          Audio = Audio,
                          Mouse = Mouse,
                          MouseWheel = MouseWheel,
                          MouseButton = MouseButton,
                          Keyboard = Keyboard,
                          Key = Key,
                          Timer = Timer,
                          Time = Time,
                          Camera = Camera,
                          Window = Window
                          }

                if run_object then
                    Object.env = env
                    Object.find = LuaProxyObject.find
                    env.Object = Object
                else
                    Script.env = env
                    env.Script = Script
                end


                 local untrusted_function = load(untrusted_code, nil, 't', env), message
                 if not untrusted_function then return nil, message end
                 return pcall(untrusted_function)
               end

               function init()
                    for i = 1, #ScriptsArray do
                       pcall(ScriptsArray[i].Init, ScriptsArray[i].env)
                    end
               end

               function update()
                    for i = 1, #ScriptsArray do
                         pcall(ScriptsArray[i].Update, ScriptsArray[i].env)
                    end
               end

               function render()
                    for i = 1, #ScriptsArray do
                         pcall(ScriptsArray[i].Render, ScriptsArray[i].env)
                    end
               end

               )");


    _fun_init = _lua["init"];
    _fun_update = _lua["update"];
    _fun_render = _lua["render"];
}

void LuaSandbox::AddScript(const std::string& origin, const std::string& script_lines){
    try{
        sol::table table = _lua.create_named_table("Script");
        _lua["run"](script_lines, false);
        _lua["push_script"]();
    }
    catch(const sol::error& ex){
        std::cerr << "Error at file: \"" << origin << "\"" << std::endl;
        std::cerr << ex.what() << std::endl;
    }
}

void LuaSandbox::AddObject(const std::string& origin, const std::string& script_lines, Object* owner){
    try{
        sol::table table = _lua.create_named_table("Object");
        _lua["run"](script_lines, true);

        LuaProxyObject* proxy = new LuaProxyObject(table, _lua["remove_object"]);
        owner->Connect(proxy);

        _lua["push_object"](proxy->GetId());
    }
    catch(const sol::error& ex){
        std::cerr << "Error at file: \"" << origin << "\"" << std::endl;
        std::cerr << ex.what() << std::endl;
    }
}

void LuaSandbox::EngineInit(){
    _fun_init();
}

void LuaSandbox::EngineUpdate(){
    _fun_update();
}

void LuaSandbox::EngineRender(){
    _fun_render();
}

void LuaSandbox::EngineCleanUp(){

}
