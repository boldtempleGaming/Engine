#include "LuaAudio.h"

void LuaAudio::bind(sol::state& lua){
    lua.new_simple_usertype<Audio>(
        "Audio",
         sol::constructors< sol::types<>, sol::types<const std::string&, bool> >(), //const std::string&, audio_type
        "setSound", &Audio::SetSound,

        "play", sol::resolve<void (int)>(&Audio::Play),
        "stop", &Audio::Stop,

        "setListener", &Audio::SetListener,
        "setPanning", &Audio::SetPanning,
        "addDistance", &Audio::AddDistance,
        "delListener", &Audio::DelListener,

        "isLoaded", &Audio::IsLoaded,
        "isPlaying", &Audio::IsPlaying,

        //"listener", sol::property(&Audio::SetListener, &Audio::GetListener),
        "dist", sol::property(&Audio::GetDistance, &Audio::SetDistance),
        "vol", sol::property(&Audio::GetVolume, &Audio::SetVolume),
        "pos", sol::property(&Audio::GetWorldPos, &Audio::SetWorldPos)
    );
}
