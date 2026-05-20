#pragma once

#include "asset_man.hpp"
#include "deps.hpp"

#include "gameplay/player/aux_powers/aux_machine.hpp"
#include "gameplay/player/aux_powers/orbital_shield.hpp"
#include "gameplay/player/primary_shots/plasma_shot.hpp"
#include "gameplay/player/secondary_shots/missile_shooter.hpp"
#include "gameplay/player/secondary_shots/secondary_machine.hpp"
#include "gameplay/player/special_shots/big_shooter.hpp"
#include "gameplay/player/special_shots/special_machine.hpp"
#include "gameplay/components/direction.hpp"
#include "gameplay/components/health.hpp"
#include "gameplay/components/hitbox.hpp"
#include "gameplay/components/position.hpp"
#include "gameplay/player/primary_shots/basic_shot.hpp"

#include "entity.hpp"
#include "systems.hpp"
#include "timer.hpp"

namespace Game {

    template<typename T>
        using uptr = std::unique_ptr<T>;

    template<typename T>
        using sptr = std::shared_ptr<T>;

    struct Player : public Engine::Entity{

            Player() {
            }

            Player(Vector2 pos) {

                this->pos = pos;
            }

            void update(double dt, Engine::GameState& sys) override; 
            void draw() override;
            void turn_invincible(double seconds);
            Rectangle get_hitbox() { return hitbox.get(pos.vec()); };
            void die(Engine::GameState& sys);
            void revive();
            bool destroy_self() override { return self_destruct; };
            void take_damage();

            double speed = 135.0f;
            int special_meter = 0;
            int upgrade = 0;

            Engine::Timer cooldown = Engine::Timer(0.5f);
            Engine::Timer graze_cooldown = Engine::Timer(0.10);

            uptr<ShootingMachine> primary_shot = std::make_unique<PlasmaShooter>();
            int primary_level = 1;

            uptr<SecondaryMachine> secondary_shot = std::make_unique<MissileShooter>();
            int secondary_level = 0;

            uptr<SpecialMachine> special_shot = std::make_unique<BigShooter>();

            uptr<AuxMachine> aux_power = std::make_unique<OrbitalShield>();;
            int aux_level = 0;

            sptr<Sound> shooting_sound = Engine::AssetMan::get_sound("space-laser");
            sptr<Texture> spritesheet = Engine::AssetMan::get_texture("player_ship");

            Position pos = Position(0.0, 0.0);
            Direction dir = Direction(0.0, 0.0);
            Hitbox hitbox = Hitbox(2.0f, 2.0f);
            Hitbox graze_range = Hitbox(42, 30);
            Health lives = Health(5);

            bool dead = false;
            bool invincible = false;
            Engine::Timer invis_timer;

            bool self_destruct = false;

    };

    enum struct PlayerMember {

        upgrade,
        special_meter,
        primary_level,
        secondary_level,
        aux_level,
        lives,
        pos_x,
        pos_y,

        special_shot,
        aux_power,
        primary_shot,

    };

    inline std::map<std::string, PlayerMember> member_to_string {
        {"upgrade", PlayerMember::upgrade},
        {"special_meter", PlayerMember::special_meter},
        {"primary_level", PlayerMember::primary_level},
        {"secondary_level", PlayerMember::secondary_level},
        {"aux_level", PlayerMember::aux_level},
        {"lives", PlayerMember::lives},
        {"pos_x", PlayerMember::pos_x},
        {"pos_y", PlayerMember::pos_y},

        {"special_shot", PlayerMember::special_shot},
        {"aux_power", PlayerMember::aux_power},
        {"primary_shot", PlayerMember::primary_shot}
    };

    struct PlayerMan {

        public:

            void update(double dt, Engine::GameState& sys);
            void draw();
            Player& get_player();
            void init_player(Vector2 position);
            void save_player(Engine::GameState& sys);
            void load_player(Engine::GameState& sys);


            void debug_ui();
            void debug_world();

        private:

            uptr<Player> m_player1;

    };

}
