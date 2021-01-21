#ifndef TURN_H
#define TURN_H

#include <chrono>
#include <thread>

class Side;

class Turn {
private:

    int hp = 0;
    int range = 0;
    int damage = 0;
    int hitspeed = 0;
    int locatie = 0; // ori e 0 ori e 42

public:

    explicit Turn(int in_locatie) {
        hp = 1000;
        range = 7;
        damage = 99;
        hitspeed = 800;
        locatie = in_locatie;
    }

    int get_damage() {
        return damage;
    }

    int get_hp() {
        return hp;
    }

    int get_locatie() const {
		return locatie;
	}

	void get_hit(int damage_primit) {
		hp -= damage_primit;
	}

	void automat(Side &Enemy);
};

#endif // !TURN_H
