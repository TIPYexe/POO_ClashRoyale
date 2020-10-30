#include "Turn.h"

void Turn::automat(Personaj& Enemy) {
    while (abs(Enemy.get_locatie() - locatie) <= range)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(hitspeed));
        Enemy.get_hit(damage);
    }
}