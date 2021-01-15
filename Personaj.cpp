#include "Personaj.h"

Personaj::Personaj() {

}

Personaj::Personaj(std::string in_nume, int in_hitspeed, int in_speed, int in_range, int in_hp, int in_damage,
                   bool in_transport, bool in_target, bool in_reset_factor) {
    nume = in_nume;
    hitspeed = in_hitspeed;
    speed = in_speed;
    range = in_range;
    hp = in_hp;
    damage = in_damage;
    transport = in_transport;
    target = in_target;
    reset_factor = in_reset_factor;
}

Personaj &Personaj::operator=(const Personaj &personaj) = default;

Personaj::Personaj(const Personaj &personaj) {
    hitspeed = personaj.hitspeed;
    speed = personaj.speed;
    range = personaj.range;
    hp = personaj.hp;
    damage = personaj.damage;
    transport = personaj.transport;
    target = personaj.target;
    reset_factor = personaj.reset_factor;
    locatie = personaj.locatie;
    nume = personaj.nume;
}

void Personaj::locatie_update() {
    if (hp > 0)
        locatie += speed;
    if (locatie < 0)
        locatie = 0;
    if (locatie > 40)
        locatie = 40;
}

int Personaj::search_enemy(Personaj Enemy) const {
    if (abs(Enemy.get_locatie() - locatie) <= range)
        return 1;
    return 0;
}

void Personaj::automat(Personaj& Enemy, Turn& Turn_inamic, Turn& Turn_echipa) {
    while (hp > 0 && Turn_echipa.get_hp() > 0 && (Enemy.get_hp() > 0 || Turn_inamic.get_hp() > 0))
    { // daca nici personajul, nici turnul din echipa lui n-au murit, continua sa joace
        if (!search_enemy(Enemy) && !search_turn(Turn_inamic))
        {
            locatie_update();
            std::this_thread::sleep_for(std::chrono::seconds(1)); // viteza pasilor e masurata pe secunda
        }
        else
        {
            if (search_enemy(Enemy)) {
                if ((Enemy.get_transport() == target) || target) // verific daca il poate ataca
                {
                    std::this_thread::sleep_for(std::chrono::milliseconds(hitspeed)); // mai intai trebuie sa treaca
                    // timpul de charge al atacului
                    if (hp > 0) // daca nu a murit intre timp, atunci ataca
                        Enemy.get_hit(damage);
                } else // daca nu il poate ataca, continua sa mearga
                {
                    locatie_update();
                    std::cout << "Reset\n";
                    Turn_inamic.reset_position((speed < 0) * 42);
                    Turn_echipa.reset_position((speed < 0) * 42);
                    std::this_thread::sleep_for(std::chrono::seconds(1)); // viteza pasilor e masurata pe secunda
                }
            }
            if (search_turn(Turn_inamic))
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(hitspeed));
                Turn_inamic.get_hit(damage);
            }
        }
    }
    if (hp <= 0)
        locatie = 100;
}

int Personaj::search_turn(Turn Tower) const {
    if (abs(Tower.get_locatie() - locatie) <= range)
        return 1;
    return 0;
}







