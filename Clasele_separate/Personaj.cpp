#include "Personaj.h"

void Personaj::locatie_update() {
    if (hp > 0)
        locatie += speed;
    if (locatie < 0)
        locatie = 0;
    if (locatie > 40)
        locatie = 40;
}

int Personaj::search_enemy(Personaj Enemy)
{
    if (abs(Enemy.get_locatie() - locatie) <= range)
        return 1;
    return 0;
}

void Personaj::copy(const Personaj& jucator, int in_locatie, int sens) {
    nume = jucator.nume;
    hitspeed = jucator.hitspeed;
    speed = jucator.speed * sens;
    range = jucator.range;
    hp = jucator.hp;
    damage = jucator.damage;
    transport = jucator.transport;
    target = jucator.target;
    reset_factor = jucator.reset_factor;
    locatie = in_locatie;
}

void Personaj::automat(Personaj& Enemy, Turn& Tower, Turn& Turn_echipa) {
    while (hp > 0 && Turn_echipa.get_hp() > 0 && (Enemy.get_hp() > 0 || Tower.get_hp() > 0))
    { // daca nici personajul, nici turnul din echipa lui n-au murit, continua sa joace
        if (!search_enemy(Enemy) && !search_turn(Tower))
        {
            locatie_update();
            std::this_thread::sleep_for(std::chrono::seconds(1)); // viteza pasilor e masurata pe secunda
        }
        else
        {
            if (search_enemy(Enemy))
                if ((Enemy.get_transport() == target) || target) // verific daca il poate ataca
                {
                    std::this_thread::sleep_for(std::chrono::milliseconds(hitspeed)); // mai intai trebuie sa treaca
                                                                                      // timpul de charge al atacului 
                    if(hp > 0) // daca nu a murit intre timp, atunci ataca
                    Enemy.get_hit(damage);
                }
                else // daca nu il poate ataca, continua sa mearga
                {
                    locatie_update();
                    std::this_thread::sleep_for(std::chrono::seconds(1)); // viteza pasilor e masurata pe secunda
                }
            if (search_turn(Tower))
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(hitspeed));
                Tower.get_hit(damage);
            }
        }
    }
    if (hp <= 0)
        locatie = 100;
}

int Personaj::search_turn(Turn Tower) {
    if (abs(Tower.get_locatie() - locatie) <= range)
        return 1;
    return 0;
}
