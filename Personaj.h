#ifndef PERSONAJ_H
#define PERSONAJ_H

#include <iostream>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <cstring>

#include "Turn.h"
#include "Turn.h"
//using namespace std;
//using namespace this_thread;

class Turn;

class Harta;

class Personaj {
private:

    //friend class Turn;

    // calitati personaj
    int hitspeed = 0; // timp (milisecunde) de charge pentru atac
    int speed = 0; // viteza de deplasare per secunda
    // pentru  a-mi simplifica viata, campul de lupta este axa numerelor
    // iar adversarului ii voi da o viteza negativa, pentru a face personajele
    // sa se apropie

    int range = 0; // distanta de la care poate ataca
    int hp = 0; // puncte de viata
    int damage = 0; // puncte de viata pe care le ia per atac
    bool transport = false; // 0 = teren; 1 = aer
    bool target = false; // 0 = ataca doar teren; 1 = ataca teren & aer
    bool reset_factor = false; // daca atacul lui are si efect de reset asupra atacului
    // inamicului
    int locatie = 0; // locatia pe campul de lupta (axa numerelor)

    // statistici lupta
    //bool engaged; // 0 = nu se lupta; 1 = se lupta

    std::string nume = "";

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

    void set_speed(int x) {
        speed *= x;
    }

    void set_locatie(int x) {
        locatie = x;
    }

    // inainteaza personajul in cazul in care mai traieste si
    // nu este intr-o batalie, in acest caz ar trebui sa stea
    // functia va fi apelata 1data/s si deci pot adauga la locatie
    // direct valoarea lui speed.
    void locatie_update();

    // cauta adversari in raza sa de atac, iar daca gaseste, starea de
    // engage devine 1 si functie se opreste
    int search_enemy(Personaj Enemy) const;

    Personaj();

    // cu acest constructor creez cartile disponibile
    Personaj(std::string in_nume, int in_hitspeed, int in_speed, int in_range, int in_hp,
             int in_damage, bool in_transport, bool in_target, bool in_reset_factor);

    int search_turn(Turn Tower) const;

    void automat(Personaj &Enemy, Turn &Turn_inamic, Turn &Echipa);

    Personaj &operator=(const Personaj &personaj);

    Personaj(const Personaj &personaj);
};

#endif // !PERSONAJ_H
