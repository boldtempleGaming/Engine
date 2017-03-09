#include "LuaCamera.h"

void LuaCamera::bind(sol::state& lua){
    lua.new_simple_usertype<Camera>("Camera",
        "pos", sol::property(&Camera::GetPos , &Camera::SetPos),
        "viewport",  sol::property(&Camera::GetViewport , &Camera::SetViewport),
        "inView", sol::resolve<bool(const Vec2&)>(&Camera::InView),
        "move", &Camera::Move
    );
}
