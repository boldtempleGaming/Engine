#include "LuaAudio.h"

void LuaAudio::bind(sol::state& lua){
    lua.new_simple_usertype<Audio>(
        "Audio",
         sol::constructors< sol::types<>, sol::types<const std::string&, bool> >(), //const std::string&, audio_type
        "setSound", &Audio::SetSound,

        "play", sol::resolve<void (int)>(&Audio::Play),
        "stop", &Audio::Stop,

        "setVolume", &Audio::SetVolume,
        "setPanning", &Audio::SetPanning,
        "setDistance", &Audio::SetDistance,

        "addDistance", &Audio::AddDistance,

        "isLoaded", &Audio::IsLoaded,
        "isPlaying", &Audio::IsPlaying
    );
}
