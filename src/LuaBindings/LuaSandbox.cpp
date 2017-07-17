#include "LuaSandbox.h"

sol::state    LuaSandbox::_lua;
sol::function LuaSandbox::_fun_init;
sol::function LuaSandbox::_fun_postinit;
sol::function LuaSandbox::_fun_update;
sol::function LuaSandbox::_fun_render;

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
    LuaDrawer::bind(_lua);

    //FIXME package.path
    _lua.script(R"(
package.path = "./../Data/?.lua"
count = 0
objects = 0
Globals = {}
ScriptsArray = {}
ObjectsArray = {}

function dump(o)
  if type(o) == 'table' then
    local s = '{ '
    for k,v in pairs(o) do
      if type(k) ~= 'number' then k = '`'..k..'`' end
      s = s .. '['..k..'] = ' .. dump(v) .. ','
    end
    return s .. '} '
  else
    return tostring(o)
  end
end

function push_script()
  count = count + 1
  table.insert(ScriptsArray, count, Script)
end

function push_object(id)
  objects = objects + 1
  ObjectsArray[objects] = Object
end

function remove_object(id)
  ObjectsArray[id] = nil
end

function create_env()
  return {
            print = print,
            math = math,
            table = table,
            pcall = pcall,
            require = require,
            dump = dump,
            Globals = globals,

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
            Window = Window,
            Color = Color,
            Drawer = Drawer
         }
end

function run(untrusted_code, run_object)
    -- run code under environment [Lua 5.2]
    -- make environment
    -- add functions you know are safe here
    local env = create_env()
    if run_object then
      Object.env = env
      Object.find = LuaProxyObject.find

      Object.new = function(table)
      return LuaProxyObject.new(table, remove_object)
    end

    env.Object = Object
    else
      Script.env = env
      env.Script = Script
    end

    local untrusted_function = load(untrusted_code, nil, 't', env), message

    if not untrusted_function then
      return nil, message
    end

    return pcall(untrusted_function)
end

function post_objects_init()
  print("post_objects_init")

  do
    local env = create_env()
    for i = 1, #ObjectsArray do
      local object = ObjectsArray[i]
      object.PostInit(object, object.DataStorage)
    end
  end -- do
end -- function

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
    _fun_postinit = _lua["post_objects_init"];
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

        sol::function remfunc = _lua["remove_object"];
        LuaProxyObject* proxy = new LuaProxyObject(table, remfunc);
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
    _fun_postinit();
}

void LuaSandbox::EngineUpdate(){
    _fun_update();
}

void LuaSandbox::EngineRender(){
    _fun_render();
}

void LuaSandbox::EngineCleanUp(){

}
