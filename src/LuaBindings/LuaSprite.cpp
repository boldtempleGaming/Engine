#include "LuaSprite.h"

class Animation;
class Sprite;

void LuaSprite::bind(sol::state &lua){

    lua.new_enum("Flip",
                 "NONE", SDL_FLIP_NONE,
                 "HORIZONTAL", SDL_FLIP_HORIZONTAL,
                 "VERTICAL", SDL_FLIP_VERTICAL
    );

    lua.new_usertype<Animation>("Animation",
            "rate", sol::property(&Animation::GetFrameRate, &Animation::SetFrameRate),
            "current", sol::property(&Animation::GetCurrentFrame, &Animation::SetCurrentFrame),
            "begin", sol::property(&Animation::GetBeginFrame, &Animation::SetBeginFrame),
            "max", sol::property(&Animation::GetMaxFrame, &Animation::SetMaxFrame)
    );

    // make usertype metatable
    lua.new_usertype<Sprite>( "Sprite",

            // 1 constructor
            sol::constructors<sol::types<>>(),

            "setTexture", sol::resolve<void(const std::string&)>(&Sprite::SetTexture),
            "draw", sol::resolve<void(const Vec2&, const Vec2&)>(&Sprite::Draw),

            // gets or set the value using member variable syntax
            "flip", sol::property(&Sprite::GetFlip, &Sprite::SetFlip),
            "angle", sol::property(&Sprite::GetAngle, &Sprite::SetAngle),

            "setFrameSize", &Sprite::SetFrameSize,
            "setAnimation", sol::resolve<void(const Animation&)>(&Sprite::SetAnimation)

           // sol::meta_function::equal_to, sol::overload(sol::resolve<bool(const Vec2&) const>( &Vec2::operator ==  ))
    );
}
