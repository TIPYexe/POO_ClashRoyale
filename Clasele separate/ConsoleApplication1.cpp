#include <iostream>
#include <thread>
#include <stdlib.h>

#include "Turn.h"
#include "Personaj.h"
#include "Harta.h"


/*
void afisare_camp(char field[], Personaj& Enemy, Personaj& Friend)
{
	while (Enemy.get_hp() > 0 && Friend.get_hp() > 0)
	{
		system("CLS");
		strcpy_s(field, 42, "........................................."); //resetez toate pozitiile cu "."
		field[Enemy.get_locatie() - 1] = Enemy.get_name()[0]; //pun initialele numelor pesonajelor acolo unde trebuie
		field[Friend.get_locatie() - 1] = Friend.get_name()[0];
		cout << field << '\n'; // afisez campul de lupta

		printf("\n");
		stats(Enemy, Friend); // afisez si statistici despre personaje

		sleep_for(chrono::milliseconds(17)); // face jocul sa fie in 60FPS, si se vede mai bine ca personajele 
											 // isi dau atacurile pe rand, deci functioneaza delay-ul
	}
}
*/

int main() {

	Personaj Carti[5];
	Carti[0] = Personaj("Vrajitor", 1400, 3, 6, 656, 256, 0, 1, 0);
	Carti[1] = Personaj("Bowler", 2500, 2, 4, 1898, 262, 0, 0, 0);
	Carti[2] = Personaj("Baby Dragon", 1500, 4, 4, 1051, 146, 1, 1, 0);
	Carti[3] = Personaj("Electro Wizard", 1800, 4, 5, 649, 210, 0, 1, 1);

	// fara aceasta declarare de aici nu pot apela thread-ul "field"
	Personaj Enemy;
	Personaj Friendly;

	Turn Inamic(0);
	Turn Prieten(42);

	Harta Field;
	//char field[] = ".........................................";

	srand(time(NULL));
	int nr = rand() % 4;
	int locatie = abs(rand() % 20 + 21); // +21 pt ca trebuie sa fie in a doua jumatate
	Enemy.copy_adv(Carti[nr], locatie);

	nr = rand() % 4;
	locatie = abs(rand() % 20 + 1);
	Friendly.copy(Carti[nr], locatie);


	// fiecare meteoda si functia de afisare a hartii+stats ruleaza pe cate un thread
	// pentru ca toate aceste functii trebuie sa ruleze simultan
	thread enemy(&Personaj::automat, ref(Enemy), ref(Friendly));     // am pasat obiectele ca referinte pentru ca altfel
	thread friendly(&Personaj::automat, ref(Friendly), ref(Enemy));  // nu se modificau valorile, si deci nu aveau relevanta 
	thread field_t(&Harta::afisare_camp, ref(Enemy), ref(Friendly)); // nici harta nici statisticile, ramaneau neschimbate

	enemy.join();
	friendly.join();
	field_t.join();


	// la finalul jocului
	system("CLS");
	if (Enemy.get_hp() > 0 && Friendly.get_hp() <= 0)
		printf("%s a invins!\n", Enemy.get_name().c_str());
	else if (Enemy.get_hp() <= 0 && Friendly.get_hp() > 0)
		printf("%s a invins!\n", Friendly.get_name().c_str());
	else
		printf("EGALITATE!\n");
	printf("\n");
	stats(Enemy, Friendly);

}
