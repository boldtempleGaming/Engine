#include "LuaTimer.h"

void LuaTimer::bind(sol::state& lua){
    lua.new_enum("Time",
                 "SECOND", Timer::SECOND,
                 "MINUTE", Timer::MINUTE,
                 "HOUR", Timer::HOUR
    );

    lua.new_simple_usertype<Timer>("Timer",
        "now", &Timer::Now,
        "reset", &Timer::Reset,
        "range", sol::property(&Timer::GetRange, &Timer::SetRange),
        "startTime", sol::property(&Timer::GetStartTime),

        "inRange", &Timer::InRange,
        "outRange", &Timer::OutRange

//        "SECOND", sol::var(&Timer::SECOND),
//        "MINUTE", sol::var(&Timer::MINUTE),
//        "HOUR", sol::var(&Timer::HOUR)
    );
}
