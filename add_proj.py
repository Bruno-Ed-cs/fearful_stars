import sys
import os

header = """#pragma once

#include "deps.hpp"

#include "gameplay/components/direction.hpp"
#include "gameplay/components/hitbox.hpp"
#include "gameplay/components/position.hpp"
#include "gameplay/projectile/i_projectile.hpp"
#include "systems.hpp"

namespace Game {{

class {0} : public IProjectile{{

public:

    {0}(Vector2 position, double speed, Vector2 direction, bool foe, int damage) :
        pos(position), orientation(direction), foe(foe), damage(damage), speed(speed) {{}}

    bool is_foe() {{ return foe; }}
    Rectangle get_hitbox() {{ return hitbox.get(pos); }}
    Vector2 get_position() {{ return pos.vec(); }}
    double get_speed() {{ return speed; }}
    const std::type_info& get_type() {{ return typeid({0}); }}
    bool destroy_self() {{ return destruct; }}
    int get_damage() {{ return damage; }}

    void update(double dt, Engine::Systems& sys);
    void draw();

    void reset(Vector2 pos, double speed, Vector2 direction, bool foe, int damage = 0);

public:

    Position pos;
    Direction orientation;
    Hitbox hitbox = Hitbox(10, 6);
    int damage;
    double speed;
    bool foe;
    bool destruct = false;

}};

}}
"""

implementation = """#include "{1}.hpp"

using namespace Game;

void {0}::update(double dt, Engine::Systems& sys) {{

}}

void {0}::draw() {{

}}

void {0}::reset(Vector2 pos, double speed, Vector2 direction, bool foe, int damage) {{

}}

"""

name = sys.argv[1].capitalize() + "Proj"

header_formatted = header.format(name)
implementation_formatted = implementation.format(name, sys.argv[1].casefold() + "_proj")

path = "./src/gameplay/projectile/" + sys.argv[1]
try:
    os.mkdir(path)
    print(f"Directory {path} created")
except:
    print(f"It was not possible to create the directory {path}")

filename = path + "/" + sys.argv[1].casefold() + "_proj.hpp"
with open(filename, "w") as file:
    file.write(header_formatted)
    print(f"File {filename} created")

filename = path + "/" + sys.argv[1].casefold() + "_proj.cpp"
with open(filename, "w") as file:
    file.write(implementation_formatted)
    print(f"File {filename} created")
