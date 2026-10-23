#pragma once
#include "deps.hpp"
#include "recycle_array.hpp"
#include "asset_man.hpp"
#include "timer.hpp"
#include "animator.hpp"
#include "components/position.hpp"
#include "components/hitbox.hpp"
#include "components/health.hpp"
#include "components/direction.hpp"

template<typename T>
using uptr = std::unique_ptr<T>;

template<typename T>
using sptr = std::shared_ptr<T>;

struct Actor {

    enum Type {
        Player = 1,
        Meteorite,


    } type;

    std::string_view shooting_sound = "";
    std::string_view spritesheet = "";
    Engine::Animator animation = {};
    Hitbox graze_range = Hitbox(0, 0);
    Hitbox hitbox = Hitbox(0, 0);
    Direction dir = Direction(0.0, 0.0);
    Health lives = Health(0);
    Position pos = Position(0.0, 0.0);
    Engine::Timer cooldown = Engine::Timer(0);
    Engine::Timer graze_cooldown = Engine::Timer(0);
    Engine::Timer invis_timer;
    Engine::Timer shooting_cooldown;
    double speed = 0;
    int aux_level = 0;
    int primary_level = 0;
    int primary_state = 0;
    int secondary_level = 0;
    int special_meter = 0;
    int upgrade = 0;
    int damage_intake = 0;
    bool dead = false;
    bool invincible = false;
};

struct Projectile {

    enum Type {
        Plasma,

    } type;

    std::string_view spritesheet = "";
    Engine::Animator animation;
    Hitbox hitbox = Hitbox{0, 0};
    Position pos;
    Direction direction{0, 0};
    double speed = 0;
    int base_damage = 0;
    int damage_output = 0;
    bool self_destruct = false;

};

struct Game {

    constexpr static int max_projectiles = 5000;

    idx player;

    Engine::RecycleArray<Actor, 500> actors;
    Engine::RecycleArray<Projectile, max_projectiles> enemy_proj;
    Engine::RecycleArray<Projectile, max_projectiles> player_proj;

    Game();

    void update();

    void draw();

};

struct PlasmaProjectile {

    static Projectile make(Position pos, Direction dir, int damage, double speed);
    static void update(idx self, Game& gm, bool foe);

};

struct Player {

    static Actor make(Position pos = {30, 30});
    static void update(idx self, Game& gm);
    static void draw(Actor& player);

};

struct Meteorite {

    static Actor make(Position pos);
    static void update(idx self, Game& gm);
    static void draw(Actor& meteorite);

};
