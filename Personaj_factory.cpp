#include "Personaj_factory.h"

Personaj Personaj_factory::BabyDragon() {
    return Personaj("Baby Dragon", 1500, 4, 4, 1051, 146, 1, 1, 4);
}

Personaj Personaj_factory::Bowler() {
    return Personaj("Bowler", 2500, 2, 4, 1898, 262, 0, 0, 5);
}

Personaj Personaj_factory::ElectroWizard() {
    return Personaj("Electro Wizard", 1800, 4, 5, 649, 210, 0, 1, 4);
}

Personaj Personaj_factory::Vrajitor() {
    return Personaj("Vrajitor", 1400, 3, 6, 656, 256, 0, 1, 5);
}
