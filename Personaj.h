#ifndef PERSONAJ_H
#define PERSONAJ_H

#include <iostream>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <cstring>

class Personaj {
private:

    //friend class Turn;

    // calitati personaj
    int hitspeed = 0; // timp (milisecunde) de charge pentru atac
    int speed = 0; // viteza de deplasare per secunda
    // pentru  a-mi simplifica viata, campul de lupta este axa numerelor
    // iar adversarului ii voi da o viteza negativa, pentru a face personajele
    // sa se apropie

    float cost = 0; // costul de elixir pentru a spawna un personaj
    int range = 0; // distanta de la care poate ataca
    int hp = 0; // puncte de viata
    int damage = 0; // puncte de viata pe care le ia per atac
    bool transport = false; // 0 = teren; 1 = aer
    bool target = false; // 0 = ataca doar teren; 1 = ataca teren & aer
    //bool reset_factor = false; // daca atacul lui are si efect de reset asupra atacului
    // inamicului
    //int locatie = 0; // locatia pe campul de lupta (axa numerelor)

    // statistici lupta
    //bool engaged; // 0 = nu se lupta; 1 = se lupta

    std::string nume = "";

public:

    float get_cost(){
        return cost;
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

    void setHp(int hp);

    int getHitspeed() const;

    bool isTarget() const;

    int get_range() const;

    Personaj();

    virtual ~Personaj();

    // cu acest constructor creez cartile disponibile
    Personaj(std::string in_nume, int in_hitspeed, int in_speed, int in_range, int in_hp,
             int in_damage, bool in_transport, bool in_target, float cost);

    Personaj &operator=(const Personaj &personaj);

    Personaj(const Personaj &personaj);
};

#endif // !PERSONAJ_H
