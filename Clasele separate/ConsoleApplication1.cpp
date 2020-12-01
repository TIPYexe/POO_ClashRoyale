#include <iostream>
#include <thread>
#include <stdlib.h>

#include "Turn.h"
#include "Personaj.h"
#include "Harta.h"



int main() {

	Personaj Carti[5];
	Carti[0] = Personaj("Vrajitor", 1400, 3, 6, 656, 256, 0, 1, 0);
	Carti[1] = Personaj("Bowler", 2500, 2, 4, 1898, 262, 0, 0, 0);
	Carti[2] = Personaj("Baby Dragon", 1500, 4, 4, 1051, 146, 1, 1, 0);
	Carti[3] = Personaj("Electro Wizard", 1800, 4, 5, 649, 210, 0, 1, 1);

	// fara aceasta declarare de aici nu pot apela thread-ul "field"
	Personaj Enemy;
	Personaj Friendly;

	Turn Inamic(42);
	Turn Prieten(0);

	Harta Field;

	srand(time(NULL));
	int nr = rand() % 4;
	int locatie = abs(rand() % 20 + 21); // +21 pt ca trebuie sa fie in a doua jumatate
	Enemy.copy(Carti[nr], locatie, -1);

	nr = rand() % 4;
	locatie = abs(rand() % 20 + 1);
	Friendly.copy(Carti[nr], locatie, 1);


	// fiecare meteoda si functia de afisare a hartii+stats ruleaza pe cate un thread
	// pentru ca toate aceste functii trebuie sa ruleze simultan
	std::thread enemy(&Personaj::automat, std::ref(Enemy), std::ref(Friendly), std::ref(Prieten), std::ref(Inamic));     // am pasat obiectele ca referinte pentru ca altfel
	std::thread friendly(&Personaj::automat, std::ref(Friendly), std::ref(Enemy), std::ref(Inamic), std::ref(Prieten));  // nu se modificau valorile, si deci nu aveau relevanta 
	std::thread turn_inamic(&Turn::automat, std::ref(Inamic), std::ref(Friendly));	
	std::thread turn_prieten(&Turn::automat, std::ref(Prieten), std::ref(Enemy));
	std::thread field_t(&Harta::afisare_camp, std::ref(Field), std::ref(Enemy), std::ref(Friendly), std::ref(Inamic), std::ref(Prieten)); // nici harta nici statisticile, ramaneau neschimbate

	enemy.join();
	friendly.join();
	turn_inamic.join();
	turn_prieten.join();
	field_t.join();
	

	// la finalul jocului
	system("CLS");
	int rezultat = Field.game_end(std::ref(Enemy), std::ref(Friendly), std::ref(Inamic), std::ref(Prieten));
	if (rezultat == 1)
		std::cout << "AM CASTIGAT!\n\n\n";
	else if (rezultat == 2)
		std::cout << "AM PIERDUT!\n\n\n";
	else
		std::cout << "EGALITATE!\n\n\n";
	Field.stats(Enemy, Friendly, Inamic, Prieten, 1);

}
