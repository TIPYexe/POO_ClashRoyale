#ifndef CONSOLEAPPLICATION1_PERSONAJ_FACTORY_H
#define CONSOLEAPPLICATION1_PERSONAJ_FACTORY_H

#include "Personaj.h"

class Personaj_factory {
public:
    static Personaj BabyDragon();

    static Personaj Bowler();

    static Personaj ElectroWizard();

    static Personaj Vrajitor();
};


#endif //CONSOLEAPPLICATION1_PERSONAJ_FACTORY_H
