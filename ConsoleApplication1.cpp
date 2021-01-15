#include <iostream>
#include <thread>
#include <cstdlib>

#include "Turn.h"
#include "Personaj.h"
#include "Harta.h"
#include "Side.h"
#include "Personaj_factory.h"



int main() {


    std::unique_ptr<Personaj[]> Carti = std::make_unique<Personaj[]>(5);

    //Personaj Carti[5];
    Carti[0] = Personaj_factory::BabyDragon();
    Carti[1] = Personaj_factory::Bowler();
    Carti[2] = Personaj_factory::BabyDragon();
    Carti[3] = Personaj_factory::ElectroWizard();

    Turn Inamic(42);
    Turn Prieten(0);

    Harta Field;

    srand(time(NULL));
    int nr = rand() % 4;
    int locatie = abs(rand() % 20 + 21); // +21 pt ca trebuie sa fie in a doua jumatate

    Side Enemy(Carti[nr], locatie, -1);
    //Enemy.copy(Carti[nr], locatie);

    nr = rand() % 4;
    locatie = abs(rand() % 20 + 1);

    Side Friendly(Carti[nr], locatie, 1);
    //Friendly.copy(Carti[nr], locatie);


    // fiecare meteoda si functia de afisare a hartii+stats ruleaza pe cate un thread
    // pentru ca toate aceste functii trebuie sa ruleze simultan
    std::thread enemy(&Personaj::automat, std::ref(Enemy), std::ref(Friendly), std::ref(Prieten),
                      std::ref(Inamic));     // am pasat obiectele ca referinte pentru ca altfel
    std::thread friendly(&Personaj::automat, std::ref(Friendly), std::ref(Enemy), std::ref(Inamic),
                         std::ref(Prieten));  // nu se modificau valorile, si deci nu aveau relevanta
    std::thread turn_inamic(&Turn::automat, std::ref(Inamic), std::ref(Friendly));
    std::thread turn_prieten(&Turn::automat, std::ref(Prieten), std::ref(Enemy));
    std::thread field_t(&Harta::afisare_camp, std::ref(Field), std::ref(Enemy), std::ref(Friendly), std::ref(Inamic),
                        std::ref(Prieten)); // nici harta nici statisticile, ramaneau neschimbate

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
