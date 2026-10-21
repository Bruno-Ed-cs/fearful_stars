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

    } type;

    double speed = 135.0f;
    int special_meter = 0;
    int upgrade = 0;
    Engine::Timer cooldown = Engine::Timer(0.5f);
    Engine::Timer graze_cooldown = Engine::Timer(0.10);
    int primary_level = 1;
    int secondary_level = 0;
    int aux_level = 0;
    std::string_view shooting_sound = "";
    std::string_view spritesheet = "";
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

    static Actor make();
    static void update(Actor& player, Game& gm);
    static void draw(Actor& player);

};
