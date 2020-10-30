#ifndef HARTA_H
#define HARTA_H

#include <chrono>
#include <thread>

#include "Personaj.h"
#include "Turn.h"

class Harta
{
private:
	char* field;

public:

	void afisare_camp(Personaj& Enemy, Personaj& Friend);
};

void stats(Personaj Enemy, Personaj Friend)
{
	printf("%s \nHP: %d \nDamage: %d \nLocatie: %d \nViteza: %d\n\n", Enemy.get_name().c_str(), Enemy.get_hp(),
		Enemy.get_damage(), Enemy.get_locatie(), Enemy.get_speed());
	printf("%s \nHP: %d \nDamage: %d \nLocatie: %d \nViteza: %d\n", Friend.get_name().c_str(), Friend.get_hp(),
		Friend.get_damage(), Friend.get_locatie(), Friend.get_speed());
}

void Harta::afisare_camp(Personaj& Enemy, Personaj& Friend) {
	while (Enemy.get_hp() > 0 && Friend.get_hp() > 0)
	{
		system("CLS");
		strcpy_s(field, 42, "........................................."); //resetez toate pozitiile cu "."
		field[Enemy.get_locatie() - 1] = Enemy.get_name()[0];			  //pun initialele numelor pesonajelor acolo unde trebuie
		field[Friend.get_locatie() - 1] = Friend.get_name()[0];

		std::cout << "___                                         ___\n";
		std::cout << "| |                                         | |\n";	 // afisez campul de lupta cu turnuri
		std::cout << "| |" << field << "| |\n";

		std::cout << "\n";
		stats(Enemy, Friend); // afisez si statistici despre personaje

		std::this_thread::sleep_for(std::chrono::milliseconds(17)); // face jocul sa fie in 60FPS, si se vede mai bine ca personajele 
											 // isi dau atacurile pe rand, deci functioneaza delay-ul
	}
}

#endif