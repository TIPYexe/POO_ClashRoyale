#ifndef SIDE_H
#define SIDE_H

#include "Personaj.h"

class Side : public Personaj {

private:

    int sens_deplasare = 0;
    int locatie = 0;

public:

    Side() :
            Personaj{}, sens_deplasare{0}, locatie{0} {
    }

    Side(const Personaj &Caracter, int locatie, int sens) : Personaj(Caracter) {
        (*this).set_speed(sens);
        (*this).set_locatie(locatie);
    }

};

#endif