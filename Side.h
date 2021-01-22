#ifndef SIDE_H
#define SIDE_H


#include "Personaj.h"
#include "Elixir.h"
#include "Turn.h"

class Side : public Personaj, public Elixir {

private:

    int sens_deplasare = 0;
    int locatie = 0;

public:

    Side();

    Side(const Personaj &Caracter, int locatie, int sens) : Personaj(Caracter),
                                                            sens_deplasare(sens * get_speed()), locatie(locatie) {
    }

    int get_locatie() const {
        return locatie;
    }

    void printElixir() const;

    Side &operator=(const Side &Caracter) {
        if (this != &Caracter)
            Personaj::operator=(Caracter);
        return *this;
    }

    // cauta adversari in raza sa de atac, iar daca gaseste, starea de
    // engage devine 1 si functie se opreste
    int search_enemy(const Side &Enemy) const {
        if (abs(Enemy.get_locatie() - locatie) <= get_range())
            return 1;
        return 0;
    }


    int search_turn(Turn &Tower) const {
        if (abs(Tower.get_locatie() - locatie) <= get_range())
            return 1;
        return 0;
    }

    void set_locatie(int locatie) {
        Side::locatie = locatie;
    }

    // inainteaza personajul in cazul in care mai traieste si
    // nu este intr-o batalie, in acest caz ar trebui sa stea
    // functia va fi apelata 1data/s si deci pot adauga la locatie
    // direct valoarea lui speed.
    void locatie_update() {
        if (get_hp() > 0) {
            locatie += sens_deplasare;
            if (locatie < 0)
                locatie = 1;
            if (locatie > 40)
                locatie = 40;
        }
    }

    void automat(Side &Enemy, Turn &Turn_inamic, Turn &Turn_echipa, int FullHP, int LocatieOriginala);

};

#endif