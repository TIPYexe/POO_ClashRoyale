#include "Personaj.h"

Personaj::Personaj() {

}

Personaj::Personaj(std::string in_nume, int in_hitspeed, int in_speed, int in_range, int in_hp, int in_damage,
                   bool in_transport, bool in_target, float in_cost) {
    nume = in_nume;
    hitspeed = in_hitspeed;
    speed = in_speed;
    range = in_range;
    hp = in_hp;
    damage = in_damage;
    transport = in_transport;
    target = in_target;
    cost = in_cost;
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
    nume = personaj.nume;
    cost = personaj.cost;
}

void Personaj::setHp(int hp) {
    Personaj::hp = hp;
}

bool Personaj::isTarget() const {
    return target;
}

int Personaj::getHitspeed() const {
    return hitspeed;
}

int Personaj::get_range() const {
    return range;
}

Personaj::~Personaj() {

}







