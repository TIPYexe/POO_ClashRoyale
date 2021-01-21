#include <iostream>
#include <thread>
#include <cstdlib>
#include "./rlutil/rlutil.h"

#include "Turn.h"
#include "Personaj.h"
#include "Harta.h"
#include "Side.h"
#include "Personaj_factory.h"
#include "Elixir.h"

int main() {


    std::unique_ptr<Personaj[]> Carti = std::make_unique<Personaj[]>(5);
    int nrPers = 2;
    //Personaj Carti[5];
    Carti[0] = Personaj_factory::BabyDragon();
    Carti[1] = Personaj_factory::Bowler();
    //Carti[2] = Personaj_factory::Vrajitor();
    //Carti[3] = Personaj_factory::ElectroWizard();

    Turn Turn_Enemy(42);
    Turn Turn_Friend(0);
    Elixir elixir_Friend;
    Elixir elixir_Enemy;

    Harta Field;

    srand(time(NULL));
    int nr = rand() % nrPers;
    int locatie = abs(rand() % 20 + 21); // +21 pt ca trebuie sa fie in a doua jumatate

    Side Pers_Enemy(Carti[nr], locatie, -1);

    int nr_2 = rand() % nrPers;
    locatie = abs(rand() % 20 + 1);

    // Daca ambele parti au acelasi personaj de bataie, lupta nu mai are sens
    try{
        if(Pers_Enemy.get_name() == Carti[nr_2].get_name()) {
            std::cout << "Personajele sunt identice, deci va fi egal. Meciul nu are sens!";
            std::this_thread::sleep_for(std::chrono::seconds(2));
            throw (Pers_Enemy.get_name());
        }
    }
    catch (std::string &nume) {
        // ii atribui partii Pers_Friend urmatorul personaj
        nr_2++;
        if(nr_2 == nrPers)
            nr_2 = 0;
    }

    Side Pers_Friend(Carti[nr_2], locatie, 1);

    // fiecare meteoda si functia de afisare a hartii+stats ruleaza pe cate un thread
    // pentru ca toate aceste functii trebuie sa ruleze simultan
    //std::thread elixir_enemy(&Elixir::automat, std::ref(elixir_Enemy), std::ref(Pers_Enemy), std::ref(Pers_Friend), std::ref(Turn_Enemy), std::ref(Turn_Friend));
    //std::thread elixir_friend(&Elixir::automat, std::ref(elixir_Friend), std::ref(Pers_Enemy), std::ref(Pers_Friend), std::ref(Turn_Enemy), std::ref(Turn_Friend));
    std::thread pers_enemy(&Side::automat, std::ref(Pers_Enemy), std::ref(Pers_Friend), std::ref(Turn_Friend),
                      std::ref(Turn_Enemy), Carti[nr].get_hp(), 41);     // am pasat obiectele ca referinte pentru ca altfel
    std::thread pers_friend(&Side::automat, std::ref(Pers_Friend), std::ref(Pers_Enemy), std::ref(Turn_Enemy),
                         std::ref(Turn_Friend), Carti[nr_2].get_hp(), 1);  // nu se modificau valorile, si deci nu aveau relevanta
    std::thread turn_enemy(&Turn::automat, std::ref(Turn_Enemy), std::ref(Pers_Friend));
    std::thread turn_friend(&Turn::automat, std::ref(Turn_Friend), std::ref(Pers_Enemy));
    std::thread field_t(&Harta::afisare_camp, std::ref(Field), std::ref(Pers_Enemy), std::ref(Pers_Friend), std::ref(Turn_Enemy),
                        std::ref(Turn_Friend)); // nici harta nici statisticile, ramaneau neschimbate


    pers_enemy.join();
    pers_friend.join();
	turn_enemy.join();
	turn_friend.join();
    field_t.join();
    //elixir_enemy.join();
    //elixir_friend.join();

	// la finalul jocului
    rlutil::cls();
	int rezultat = Harta::game_end(std::ref(Pers_Enemy), std::ref(Pers_Friend), std::ref(Turn_Enemy), std::ref(Turn_Friend));
	if (rezultat == 1)
		std::cout << "AM CASTIGAT!\n\n\n";
	else if (rezultat == 2)
		std::cout << "AM PIERDUT!\n\n\n";
	else
		std::cout << "EGALITATE!\n\n\n";
	Field.stats(Pers_Enemy, Pers_Friend, Turn_Enemy, Turn_Friend, 1);
}
