#include "Personaj.h"

void Personaj::automat(Personaj& Enemy, Turn Tower) {
    while (Enemy.get_hp() > 0 && hp > 0)
    {
        if (!search_enemy(Enemy) && !search_turn(Tower))
        {
        e:
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
                    Enemy.get_hit(damage);
                }
                else
                    goto e;
            if (search_turn(Tower))
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(hitspeed));
                Tower.get_hit(damage);
            }
        }
    }
}

int Personaj::search_turn(Turn Tower) {
    if (abs(Tower.get_locatie() - locatie) <= range)
        return 1;
    return 0;
}