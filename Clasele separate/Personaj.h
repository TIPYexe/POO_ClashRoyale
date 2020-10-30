#ifndef PERSONAJ_H
#define PERSONAJ_H

#include <iostream>
#include <chrono>
#include <thread>
#include <stdlib.h>
#include <string.h>

#include "Turn.h"

using namespace std;
using namespace this_thread;

//class Turn;

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

	string nume;

public:

	int get_locatie() {
		return locatie;
	}

	int get_hp() {
		return hp;
	}

	string get_name() {
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
	void locatie_update() {
		if (hp > 0)
			locatie += speed;
		if (locatie < 0)
			locatie = 0;
		if (locatie > 40)
			locatie = 40;
	}

	// cauta adversari in raza sa de atac, iar daca gaseste, starea de
	// engage devine 1 si functie se opreste
	/*
	void search(char field[])
	{
		for (int i = locatie - range - 1; i < locatie + range; i++)
		{
			if(i>=0 && i<=40 && i!=(locatie-1))
				if (field[i] != '.')
				{
					engaged = 1;
					break;
				}
		}
	}
	*/

	int search_enemy(Personaj Enemy)
	{
		if (abs(Enemy.get_locatie() - locatie) <= range)
			return 1;
		return 0;
	}

	int search_turn(Turn Tower) {
		if (abs(Tower.get_locatie() - locatie) <= range)
			return 1;
		return 0;
	}

	void automat(Personaj& Enemy, Turn Tower) {
		while (Enemy.get_hp() > 0 && hp > 0)
		{
			if (!search_enemy(Enemy) && !search_turn(Tower))
			{
			e:
				locatie_update();
				this_thread::sleep_for(std::chrono::seconds(1)); // viteza pasilor e masurata pe secunda
			}
			else
			{
				if (search_enemy(Enemy))
					if ((Enemy.get_transport() == target) || target) // verific daca il poate ataca
					{
						this_thread::sleep_for(std::chrono::milliseconds(hitspeed)); // mai intai trebuie sa treaca 
																   // timpul de charge al atacului
						Enemy.get_hit(damage);
					}
					else
						goto e;
				if (search_turn(Tower))
				{
					this_thread::sleep_for(std::chrono::milliseconds(hitspeed));
					Tower.get_hit(damage);
				}
			}
		}
	}

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
	Personaj(string in_nume, int in_hitspeed, int in_speed, int in_range, int in_hp,
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
	void copy(const Personaj& jucator, int in_locatie) {
		nume = jucator.nume;
		hitspeed = jucator.hitspeed;
		speed = jucator.speed;
		range = jucator.range;
		hp = jucator.hp;
		damage = jucator.damage;
		transport = jucator.transport;
		target = jucator.target;
		reset_factor = jucator.reset_factor;
		locatie = in_locatie;
	}

	// cu aceasta functie atribui adversarul cu care ne jucam in aceasta tura
	// diferenta este ca el trebuie sa mearga invers
	void copy_adv(const Personaj& jucator, int in_locatie) {
		nume = jucator.nume;
		hitspeed = jucator.hitspeed;
		speed = jucator.speed;
		range = jucator.range;
		hp = jucator.hp;
		damage = jucator.damage;
		transport = jucator.transport;
		target = jucator.target;
		reset_factor = jucator.reset_factor;
		locatie = in_locatie;
		speed *= -1;
	}

};

#endif // !PERSONAJ_H