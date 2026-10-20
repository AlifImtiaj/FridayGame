#pragma once
#include "pch.h"
#include <SDL3_mixer/SDL_mixer.h>


namespace Friday {
    class Sound {
    private:
        MIX_Mixer* m_mixer = nullptr;
        MIX_Track* m_track = nullptr;
        MIX_Audio* m_audio = nullptr;

        std::string m_filepath;

        SDL_PropertiesID m_props;

    public:
        Sound() = default;
        ~Sound();

        
    private:


    public:
        bool Init(MIX_Mixer* mixer);

        void AddAudio(const std::string& filepath);
        void Play();
        void Stop();
    
    };
}