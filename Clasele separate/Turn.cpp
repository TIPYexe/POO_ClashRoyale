#include "Turn.h"

void Turn::automat(Personaj& Enemy) {
    while (hp > 0 && Enemy.get_hp() > 0)
        if(abs(Enemy.get_locatie() - locatie) <= range)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(hitspeed));
        if(hp>0)
        Enemy.get_hit(damage);
    }
}
