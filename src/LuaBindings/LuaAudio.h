#ifndef LUAAUDIO_H
#define LUAAUDIO_H

#include <sol.hpp>
#include "Core/Audio.h"

namespace LuaAudio {
    void bind(sol::state& lua);
}

#endif // LUAAUDIO_H
