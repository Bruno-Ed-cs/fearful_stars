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

    Direction dir = Direction(0.0, 0.0);
    Engine::Timer cooldown = Engine::Timer(0.5f);
    Engine::Timer graze_cooldown = Engine::Timer(0.10);
    Engine::Timer invis_timer;
    Engine::Timer shooting_cooldown;
    Health lives = Health(5);
    Hitbox graze_range = Hitbox(42, 30);
    Hitbox hitbox = Hitbox(2.0f, 2.0f);
    Position pos = Position(0.0, 0.0);
    bool dead = false;
    bool invincible = false;
    double speed = 135.0f;
    int aux_level = 0;
    int primary_level = 1;
    int primary_state = 0;
    int secondary_level = 0;
    int special_meter = 0;
    int upgrade = 0;
    Engine::Animator animation = {};
    std::string_view shooting_sound = "";
    std::string_view spritesheet = "";
};

struct Projectile {

    enum Type {
        Plasma,

    } type;

    bool foe = false;
    Hitbox hitbox = Hitbox{5, 5};
    Position pos;
    double speed = 0;
    Direction direction{0, 0};
    int damage = 1;
    bool self_destruct = false;
    std::string_view spritesheet;
    Engine::Animator animation;

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
    static void update(Projectile& plasma, Game& gm);

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
