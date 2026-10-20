#include "Sound.h"

Friday::Sound::~Sound() {
    if (m_audio) MIX_DestroyAudio(m_audio);
    if (m_props) SDL_DestroyProperties(m_props);
    if (m_track) MIX_DestroyTrack(m_track);
}

bool Friday::Sound::Init(MIX_Mixer* mixer) {
    m_mixer = mixer;
    m_track = MIX_CreateTrack(m_mixer);

    if (!m_track) {
        SDL_Log("Failed to create track. Error: %s", SDL_GetError());
        return false;
    }

    m_props = SDL_CreateProperties();

    if (!m_props) {
        SDL_Log("Failed to create properties. Error: %s", SDL_GetError());
        return false;
    }

    SDL_SetNumberProperty(m_props, MIX_PROP_PLAY_LOOPS_NUMBER, 0);

    return true;
}

void Friday::Sound::AddAudio(const std::string &filepath) {
    m_audio = MIX_LoadAudio(m_mixer, filepath.c_str(), true);
    if (!m_audio) {
        SDL_Log("Failed to create audio. Error: %s\n", SDL_GetError());
    }
    MIX_SetTrackAudio(m_track, m_audio);
}

void Friday::Sound::Play() {
    if (!m_mixer || !m_audio || !m_track)
        return;
    MIX_PlayTrack(m_track, m_props);
}

void Friday::Sound::Stop() {
    if (MIX_TrackPlaying(m_track))
        MIX_PauseTrack(m_track);
}
