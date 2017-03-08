#include "LuaVec2.h"

void LuaVec2::bind(sol::state& lua){
    // make usertype metatable
    lua.new_usertype<Vec2>( "Vec2",

            // 2 constructors
            sol::constructors<sol::types<>,
                              sol::types<const float&, const float&>
                             >(),

            // read and write variables
            "x", &Vec2::x,
            "y", &Vec2::y,

            // typical member function that returns a variable
            "dot", &Vec2::Dot,
            "normalize", &Vec2::Normalize,
            "getRotated", &Vec2::GetRotated,

            // gets or set the value using member variable syntax
            "length", sol::property(&Vec2::GetLength),
            "sqrLength", sol::property(&Vec2::GetSqrLength),
            "angle", sol::property(&Vec2::GetAngle, &Vec2::Rotate),
            "normalized", sol::property(&Vec2::GetNormalized),


            sol::meta_function::equal_to, sol::overload(sol::resolve<bool(const Vec2&) const>( &Vec2::operator ==  )),
            sol::meta_function::addition, &operator+,
            sol::meta_function::subtraction, &operator-,
            sol::meta_function::multiplication, sol::overload(sol::resolve<const Vec2(const Vec2&, const Vec2&)>( & operator* ),
                                                              sol::resolve<const Vec2(const Vec2&, const float&)>( & operator* )
                                                              ),
            "__unm", [](const Vec2& v){
              return Vec2(-v.x, -v.y);
            },
            "__tostring", [](const Vec2& v) {
                std::stringstream ss;
                ss << "(" <<  v.x << ", " << v.y << ")";
                return ss.str();
            },
            "__concat", [](std::string str, const Vec2& v){
                std::stringstream ss;
                ss << str << "(" << v.x << ", " << v.y << ")";
                return ss.str();
            },

            "equalTo", &Vec2::EqualTo,

            "ZERO", sol::var(&Vec2::ZERO),
            "UP", sol::var(&Vec2::UP),
            "DOWN", sol::var(&Vec2::DOWN),
            "LEFT", sol::var(&Vec2::LEFT),
            "RIGHT", sol::var(&Vec2::RIGHT)
    );
}
