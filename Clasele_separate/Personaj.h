#ifndef PERSONAJ_H
#define PERSONAJ_H

#include <iostream>
#include <chrono>
#include <thread>
#include <stdlib.h>
#include <string.h>

#include "Turn.h"

//using namespace std;
//using namespace this_thread;

class Turn;
class Harta;

class Personaj
{
private:

	//friend class Turn;

	// calitati personaj
	int hitspeed; // timp (milisecunde) de charge pentru atac
	int speed; // viteza de deplasare per secunda
				 // pentru  a-mi simplifica viata, campul de lupta este axa numerelor
				 // iar adversarului ii voi da o viteza negativa, pentru a face personajele
				 // sa se apropie

	int range; // distanta de la care poate ataca
	int hp; // puncte de viata 
	int damage; // puncte de viata pe care le ia per atac
	bool transport; // 0 = teren; 1 = aer
	bool target; // 0 = ataca doar teren; 1 = ataca teren & aer
	bool reset_factor; // daca atacul lui are si efect de reset asupra atacului
					   // inamicului
	int locatie; // locatia pe campul de lupta (axa numerelor)

	// statistici lupta
	//bool engaged; // 0 = nu se lupta; 1 = se lupta

	std::string nume;

public:

	int get_locatie() {
		return locatie;
	}

	int get_hp() {
		return hp;
	}

	std::string get_name() {
		return nume;
	}

	int get_speed() {
		return speed;
	}

	int get_damage() {
		return damage;
	}

	bool get_transport() {
		return transport;
	}

	void get_hit(int damage_enemy) {
		//cout << nume << " si-a luat damage. HP: " << hp <<"\n";
		hp -= damage_enemy;
	}

	// inainteaza personajul in cazul in care mai traieste si
	// nu este intr-o batalie, in acest caz ar trebui sa stea
	// functia va fi apelata 1data/s si deci pot adauga la locatie
	// direct valoarea lui speed.
	void locatie_update();

	// cauta adversari in raza sa de atac, iar daca gaseste, starea de
	// engage devine 1 si functie se opreste
	int search_enemy(Personaj Enemy);

	Personaj() {
		nume = "";
		hitspeed = 0;
		speed = 0;
		range = 0;
		hp = 0;
		damage = 0;
		transport = 0;
		target = 0;
		reset_factor = 0;
		//engaged = 0;
	}

	// cu acest constructor creez cartile disponibile
	Personaj(std::string in_nume, int in_hitspeed, int in_speed, int in_range, int in_hp,
		int in_damage, bool in_transport, bool in_target, bool in_reset_factor) {
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

	// cu aceasta functie atribui personajul cu care ne jucam in aceasta tura
	void copy(const Personaj& jucator, int in_locatie, int sens);

	int search_turn(Turn Tower);

	void automat(Personaj& Enemy, Turn& Tower, Turn& Echipa);
};

#endif // !PERSONAJ_H
