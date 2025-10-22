#include "music_man.hpp"
#include "raylib.h"

using MusicRef = std::shared_ptr<Music>;
template<typename T>
using vector = std::vector<T>;

using namespace Engine;

void MusicMan::init() {
    m_volume = 1.0;
    m_pitch = 1.0;
    m_buffer = vector<MusicRef>();

};


void MusicMan::update() {

    if (m_buffer.empty())
        return;

    SetMusicVolume(*m_buffer.front(), m_volume);
    SetMusicPitch(*m_buffer.front(), m_pitch);

    UpdateMusicStream(*m_buffer.front());

    switch (m_cur_mode) {

        case Mode::loop:
            loop();
            break;

        case Mode::one_shot:
            one_shot();
            break;

        case Mode::playlist:
            playlist();
            break;
    }

}

void MusicMan::add_music_to_buffer(MusicRef music_ref) {

    m_buffer.push_back(music_ref);

}

void MusicMan::set_mode(Mode mode) {

    m_cur_mode = mode;

}

void MusicMan::loop() {

    double duration = GetMusicTimeLength(*m_buffer.front());
    double curr_time = GetMusicTimePlayed(*m_buffer.front());

    if (curr_time >= duration) {

        SeekMusicStream(*m_buffer.front(), 0.0);
    }


}

void MusicMan::one_shot() {

}

void MusicMan::playlist() {

}

void MusicMan::clean() {

    m_buffer.clear();
}

void MusicMan::set_pitch(double pitch) {

    m_pitch = pitch;

}

void MusicMan::reset_pitch() {

    m_pitch = 1.0;

}

void MusicMan::set_volume(double volume) {

    m_volume = volume;

}

void MusicMan::reset_volumet() {

    m_volume = 1.0;

}


void MusicMan::start_music() {

    if (m_buffer.empty())
        return;

    PlayMusicStream(*m_buffer.front());

    if (!IsMusicStreamPlaying(*m_buffer.front())) 
        ResumeMusicStream(*m_buffer.front());
}

void MusicMan::stop_music() {

    if (m_buffer.empty()) 
        return;

    StopMusicStream(*m_buffer.front());

}




