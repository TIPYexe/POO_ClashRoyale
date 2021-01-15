/*
Nicolescu Robert Alexandru
Grupa 252
MinGW 10.2.0
Tutore: Micluta Marius
*/

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
