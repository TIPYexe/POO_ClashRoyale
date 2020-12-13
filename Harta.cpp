#include "Harta.h"

int Harta::game_end(Personaj& Enemy, Personaj& Friend, Turn& Inamic, Turn& Prieten)
{
    int numar = (Enemy.get_hp() > 0) * 8 + (Inamic.get_hp() > 0) * 4 + (Friend.get_hp() > 0) * 2 + (Prieten.get_hp() > 0) * 1;
    // o sa fac operatii pe biti, pozitiile din numar in binar:
    // Enemy, Friend, Inamic, Prieten (0,0,0,0)

    if (numar == 5 || numar == 10)
        return 0;

    if (numar == 1 || numar == 2 || numar == 3 || numar == 9 || numar == 11)
        return 1; // castigam noi

    if (numar == 4 || numar == 6 || numar == 8 || numar == 12 || numar == 14)
        return 2; // castiga adversarul

    return -1;
}

void Harta::stats(Personaj Enemy, Personaj Friend, Turn Inamic, Turn Prieten, int i)
{
    printf("-------PERSONAJE-------\n");

    if (Enemy.get_hp() > 0 || i)
        printf("ENEMY: %s \nHP: %d \nDamage: %d \nLocatie: %d \nViteza: %d\n\n", Enemy.get_name().c_str(), Enemy.get_hp(),
            Enemy.get_damage(), Enemy.get_locatie(), Enemy.get_speed());

    if (Friend.get_hp() > 0 || i)
        printf("FRIENDLY: %s \nHP: %d \nDamage: %d \nLocatie: %d \nViteza: %d\n\n", Friend.get_name().c_str(), Friend.get_hp(),
            Friend.get_damage(), Friend.get_locatie(), Friend.get_speed());

    printf("--------TURNURI--------\n");

    if (Inamic.get_hp() > 0 || i)
        printf("Inamic \nHP: %d \nDamage: %d \nLocatie: %d\n\n", Inamic.get_hp(), Inamic.get_damage(), Inamic.get_locatie());

    if (Prieten.get_hp() > 0 || i)
        printf("Prieten \nHP: %d \nDamage: %d\nLocatie: %d\n", Prieten.get_hp(), Prieten.get_damage(), Prieten.get_locatie());
}

void Harta::afisare_camp(Personaj& Enemy, Personaj& Friend, Turn& Inamic, Turn& Prieten) {
    while (game_end(Enemy, Friend, Inamic, Prieten) == -1)
    {
        //system("CLS");
        strcpy(field, "........................................."); //resetez toate pozitiile cu "."
        field[Enemy.get_locatie() - 1] = Enemy.get_name()[0];			  //pun initialele numelor pesonajelor acolo unde trebuie
        field[Friend.get_locatie() - 1] = Friend.get_name()[0];

        std::cout << "___                                         ___\n";
        std::cout << "| |                                         | |\n";	 // afisez campul de lupta cu turnuri
        std::cout << "| |" << field << "| |\n";

        std::cout << "\n";
        stats(Enemy, Friend, Inamic, Prieten, 0); // afisez si statistici despre personaje

        std::this_thread::sleep_for(std::chrono::milliseconds(500)); // face jocul sa fie in 60FPS, si se vede mai bine ca personajele
        // isi dau atacurile pe rand, deci functioneaza delay-ul
    }
}

