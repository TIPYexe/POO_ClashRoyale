#include "Harta.h"
#include "Personaj_factory.h"
#include "Side.h"
#include "./rlutil/rlutil.h"
#include <iostream>

int Harta::game_end(Side& Pers_Enemy, Side& Pers_Friend, Turn& Turn_Enemy, Turn& Turn_Friend)
{
    int numar = (Pers_Enemy.get_hp() > 0) * 8 + (Turn_Enemy.get_hp() > 0) * 4 + (Pers_Friend.get_hp() > 0) * 2 + (Turn_Friend.get_hp() > 0) * 1;
    // numar in binar = Pers_Enemy, Pers_Friend, Turn_Enemy, Turn_Friend (in viata = 1, mort = 0)
    // ex: toate entitatile in viata: 1111
    // Convertesc numar in decimal si fac verificarile
    if (numar == 5 || numar == 10)
        return 0; // iese egal

    if (numar == 1 || numar == 2 || numar == 3 || numar == 9 || numar == 11)
        return 1; // castigam noi

    if (numar == 4 || numar == 6 || numar == 8 || numar == 12 || numar == 14)
        return 2; // castiga adversarul

    return -1;
}

void Harta::stats(Side &Pers_Enemy, Side &Pers_Friend, Turn &Turn_Enemy, Turn &Turn_Friend, int i)
{
    printf("\n-------PERSONAJE-------\n\n");

    if (Pers_Enemy.get_hp() > 0 || i)
        printf("ENEMY: %s \nHP: %d \nDamage: %d \nLocatie: %d \nViteza: %d\n\n", Pers_Enemy.get_name().c_str(), Pers_Enemy.get_hp(),
            Pers_Enemy.get_damage(), Pers_Enemy.get_locatie(), Pers_Enemy.get_speed());

    if (Pers_Friend.get_hp() > 0 || i)
        printf("FRIENDLY: %s \nHP: %d \nDamage: %d \nLocatie: %d \nViteza: %d\n\n", Pers_Friend.get_name().c_str(), Pers_Friend.get_hp(),
            Pers_Friend.get_damage(), Pers_Friend.get_locatie(), Pers_Friend.get_speed());

    printf("\n--------TURNURI--------\n\n");

    if (Turn_Enemy.get_hp() > 0 || i)
        printf("Turn_Enemy \nHP: %d \nDamage: %d \nLocatie: %d\n\n", Turn_Enemy.get_hp(), Turn_Enemy.get_damage(), Turn_Enemy.get_locatie());

    if (Turn_Friend.get_hp() > 0 || i)
        printf("Turn_Friend \nHP: %d \nDamage: %d\nLocatie: %d\n", Turn_Friend.get_hp(), Turn_Friend.get_damage(), Turn_Friend.get_locatie());

    if(i != 1) {
        printf("\n--------ELIXIR--------\n\n");

        // aici folosesc functia din clasa derivata
        Pers_Enemy.printElixir();

        // aici folosesc functia din clasa de baza

        printf("Elixir Friend: ");
        Pers_Friend.Elixir::printElixir();

        //printf("Elixir Enemy: %.1f \nEnemy cost: %.1f\n", Elixir_Enemy.getElixir(), Pers_Enemy.get_cost());
        //printf("Elixir Friend: %.1f\n", Elixir_Friend.getElixir());
    }
}

void Harta::afisare_camp(Side& Pers_Enemy, Side& Pers_Friend, Turn& Turn_Enemy, Turn& Turn_Friend) {
    while (game_end(Pers_Enemy, Pers_Friend, Turn_Enemy, Turn_Friend) == -1)
    {
        //system("CLS");
        rlutil::cls();
        strcpy(field, "........................................."); //resetez toate pozitiile cu "."
        if (Pers_Enemy.get_locatie() != 100)
            field[Pers_Enemy.get_locatie() - 1] = Pers_Enemy.get_name()[0];			  //pun initialele numelor pesonajelor acolo unde trebuie
        if (Pers_Friend.get_locatie() != 100)
            field[Pers_Friend.get_locatie() - 1] = Pers_Friend.get_name()[0];

        rlutil::setColor(1);
        std::cout << "___";
        rlutil::setColor(4);
        std::cout<<"                                         ___\n";
        rlutil::setColor(1);
        std::cout << "| |";
        rlutil::setColor(4);
        std::cout<<"                                         | |\n";	 // afisez campul de lupta cu turnuri
        rlutil::setColor(1);
        std::cout << "| |" ;

        for(int i=0; i < 41; i++)
        {
            if(field[i]=='.')
                rlutil::setColor(15);

            // Enemy cu rosu
            if(i == Pers_Enemy.get_locatie() - 1)
                rlutil::setColor(4);

            // Friendly in albastru
            if(i == Pers_Friend.get_locatie() - 1)
                rlutil::setColor(1);

            std::cout << field[i];
        }

        rlutil::setColor(4);
        std::cout << "| |\n";

        // revenim la alb pentru restul datelor
        rlutil::setColor(15);

        std::cout << "\n";
        stats(Pers_Enemy, Pers_Friend, Turn_Enemy, Turn_Friend, 0); // afisez si statistici despre personaje

        std::this_thread::sleep_for(std::chrono::milliseconds(500)); // face jocul sa fie in 60FPS, si se vede mai bine ca personajele
        // isi dau atacurile pe rand, deci functioneaza delay-ul
    }
}

