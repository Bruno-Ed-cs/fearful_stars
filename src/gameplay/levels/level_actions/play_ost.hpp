#pragma once

#include "asset_man.hpp"
#include "deps.hpp"
#include "gameplay/levels/i_action.hpp"
#include "systems.hpp"
#include "music_man.hpp"

namespace Game {

class PlayOstAction : public IAction {

    std::shared_ptr<Music> m_ost;

public:

    PlayOstAction(const std::string& music_name) {

        m_ost = Engine::AssetMan::get_music(music_name);
    }

    bool execute(Engine::Systems* sys, double dt) {

        sys->music->set_mode(Engine::MusicMan::Mode::loop);
        sys->music->add_music_to_buffer(m_ost);
        sys->music->start_music();

        return true;
    };

    void reset() {

    };
};

}
