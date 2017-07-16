#include "LuaProxyObject.h"
#include <memory>

void LuaProxyObject::bind(sol::state& lua){
    lua.new_simple_usertype<Object>("LuaObject",
        sol::constructors<sol::types<>>(),
        "find", &Object::FindByLabel,
        "connect", &Object::Connect,
        "delete", &Object::DeleteLater,
        "disconnect", &Object::Disconnect,
        "move",  &Object::Move,
        "owner",  sol::property(&Object::GetOwner),
        "globalPos", sol::property(&Object::GetGlobalPos),
        "localPos", sol::property(&Object::GetPos, &Object::SetPos),
        "size", sol::property(&Object::GetSize, &Object::SetSize),
        "vel", sol::property(&Object::GetVel, &Object::SetVel),
        "id", sol::property(&Object::GetId),
        "label", sol::property(&Object::GetLabel, &Object::SetLabel)
    );

    lua.new_simple_usertype<LuaProxyObject>("LuaProxyObject",
         sol::constructors<sol::types<sol::table, sol::function>>(),
         sol::base_classes, sol::bases<Object>()
    );
}

LuaProxyObject::LuaProxyObject(sol::table lua_table, sol::function fun_delete){
    BindScriptFunctions(lua_table, fun_delete);
    _fun_init(this, _data_storage);
}

LuaProxyObject::~LuaProxyObject(){
    _fun_cleanup(this, _data_storage);
    _fun_delete_object(this->GetId());
}

void LuaProxyObject::OnPostInit(){
    _fun_postinit(this, _data_storage);
}

void LuaProxyObject::OnUpdate(){
     _fun_update(this, _data_storage);
}

void LuaProxyObject::OnRender(){
    _fun_render(this, _data_storage);
}

void LuaProxyObject::OnTopMouseEvent(){

}

void LuaProxyObject::OnCollide(Object* obj){

}

void LuaProxyObject::BindScriptFunctions(sol::table& lua_table, sol::function& fun_delete){
    _fun_delete_object = fun_delete;
    _fun_init = lua_table["Init"];
    _fun_postinit = lua_table["PostInit"];
    _fun_update = lua_table["Update"];
    _fun_render = lua_table["Render"];
    _fun_collide = lua_table["Collide"];
    _fun_cleanup = lua_table["Cleanup"];

    _data_storage = lua_table.create_named("DataStorage");
}
