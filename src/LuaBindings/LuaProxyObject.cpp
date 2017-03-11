#include "LuaProxyObject.h"
#include <memory>

void LuaProxyObject::bind(sol::state& lua){
    lua.new_simple_usertype<Object>("LuaObject",
        "delete", &Object::DeleteLater,
        "connect", &Object::Connect,
        "disconnect", &Object::Disconnect,
        "move",  &Object::Move,
        "owner",  sol::property(&Object::GetOwner),
        "pos", sol::property(&Object::GetGlobalPos, &Object::GetGlobalPos),
        "localPos", sol::property(&Object::GetPos, &Object::GetPos),
        "size", sol::property(&Object::GetSize, &Object::SetSize),
        "vel", sol::property(&Object::GetVel, &Object::SetVel),
        "id", sol::property(&Object::GetId)
    );

    lua.new_simple_usertype<LuaProxyObject>("LuaProxyObject",
         sol::base_classes, sol::bases<Object>()
    );
}

LuaProxyObject::LuaProxyObject(sol::table& lua_table, const sol::function &fun_delete){
    BindScriptFunctions(lua_table, fun_delete);
    _fun_init(this, _data_storage);
}

LuaProxyObject::~LuaProxyObject(){
    _fun_cleanup(this, _data_storage);
    _fun_delete_object(this->GetId());
}

void LuaProxyObject::OnUpdate(){
     _fun_update(this, _data_storage);
}

void LuaProxyObject::OnRender(){
    _fun_render(this, _data_storage);
}

void LuaProxyObject::OnClick(){

}

void LuaProxyObject::OnCollide(Object* obj){

}

void LuaProxyObject::BindScriptFunctions(sol::table& lua_table,  const sol::function& fun_delete){
    _fun_delete_object = fun_delete;
    _fun_init = lua_table["Init"];
    _fun_update = lua_table["Update"];
    _fun_render = lua_table["Render"];
    _fun_collide = lua_table["Collide"];
    _fun_cleanup = lua_table["Cleanup"];

    _data_storage = lua_table.create_named("DataStorage");
}
