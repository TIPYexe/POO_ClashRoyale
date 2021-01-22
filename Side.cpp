#include "Side.h"

void Side::automat(Side &Enemy, Turn &Turn_inamic, Turn &Turn_echipa, int FullHP, int LocatieOriginala) {
    while (Harta::game_end(Enemy, *this, Turn_inamic, Turn_echipa) == -1) {

        Elixir::automat();

        // daca nici personajul, nici turnul din echipa lui n-au murit, continua sa joace
        if (!search_enemy(Enemy) && !search_turn(Turn_inamic)) {
            locatie_update();
            std::this_thread::sleep_for(std::chrono::seconds(1)); // viteza pasilor e masurata pe secunda
        } else {
            if (search_turn(Turn_inamic)) {
                std::this_thread::sleep_for(std::chrono::milliseconds(getHitspeed()));
                Turn_inamic.get_hit(get_damage());
            }
            if (search_enemy(Enemy)) {
                if ((Enemy.get_transport() == isTarget()) || isTarget()) // verific daca il poate ataca
                {
                    std::this_thread::sleep_for(
                            std::chrono::milliseconds(getHitspeed())); // mai intai trebuie sa treaca
                    // timpul de charge al atacului
                    if (get_hp() > 0) // daca nu a murit intre timp, atunci ataca
                        Enemy.get_hit(get_damage());
                } else // daca nu il poate ataca, continua sa mearga
                {
                    locatie_update();
                    std::this_thread::sleep_for(std::chrono::seconds(1)); // viteza pasilor e masurata pe secunda
                }
            }
        }
        if (get_hp() <= 0) {
            locatie = 100;
            if (getElixir() >= get_cost()) {
                spendElixir(get_cost());
                std::this_thread::sleep_for(std::chrono::seconds(5));
                setHp(FullHP);
                set_locatie(LocatieOriginala);
            }
        }
    }
}

void Side::printElixir() const {
    if(sens_deplasare < 0)
        printf("Elixir Enemy: %.2f \n", getElixir());
    else
        printf("Elixir Friend: %.2f \n", getElixir());
}

Side::Side() {}

