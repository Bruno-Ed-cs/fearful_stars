#include "shooting_machine.hpp"
#include "deps.hpp"
#include "basic_shot.hpp"
#include "plasma_shot.hpp"

namespace Game {
using string = std::string;

enum struct MachineType {
    BasicShooter,
    PlasmaShooter,

};

std::map<string, MachineType> types_table {

    {"BasicShooter", MachineType::BasicShooter},
    {"PlasmaShooter", MachineType::PlasmaShooter},
};

ShootingMachine* make_shooting_machine(std::string shot_type) {

    if (!types_table.contains(shot_type)) return nullptr;

    MachineType type = types_table[shot_type];
    ShootingMachine* machine;

    switch (type) {

        case MachineType::BasicShooter:
            machine = new BasicShooter();
            break;

        case MachineType::PlasmaShooter:
            machine = new PlasmaShooter();
            break;

    }

    return machine;
}

}
