#ifndef TURN_H
#define TURH_H

#include <chrono>
#include <thread>

#include "Personaj.h"
//class Personaj;

class Turn
{
private:
	
	//friend class Personaj;
	
	int hp;
	int range;
	int damage;
	int hitspeed;
	int locatie; // ori e 0 ori e 42

public:

	Turn(int in_locatie) {
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

	int get_locatie() {
		return locatie;
	}

	void get_hit(int damage_primit) {
		hp -= damage_primit;
	}

	void automat(Personaj& Enemy) {
		while (abs(Enemy.get_locatie() - locatie) <= range)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(hitspeed));
			Enemy.get_hit(damage);
		}
	}

};

#endif // !TURN_H