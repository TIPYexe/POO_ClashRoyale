#include <iostream>
#include <chrono>
#include <thread>
#include <stdlib.h>
#include <time.h>
#include <string.h>

using namespace std;
using namespace this_thread;
using namespace chrono;

class Personaj
{
private:

    // calitati personaj
    int hitspeed; // timp (milisecunde) de charge pentru atac
    float speed; // viteza de deplasare per secunda
                 // pentru  a-mi simplifica viata, campul de lupta este axa numerelor
                 // iar adversarului ii voi da o viteza negativa, pentru a face personajele
                 // sa se apropie

    float range; // distanta de la care poate ataca
    int hp; // puncte de viata (100 = maxim, 0 = mort)
    int damage; // puncte de viata pe care le ia per atac
    bool transport; // 0 = teren; 1 = aer
    bool target; // 0 = teren; 1 = teren & aer
    bool reset_factor; // daca atacul lui are si efect de reset asupra atacului
                       // inamicului

    // statistici lupta
    bool engaged = 0; // 0 = nu se lupta; 1 = se lupta

    string nume;

public:

    float locatie; // locatia pe campul de lupta (axa numerelor)

    int get_hp() {
        return hp;
    }

    void get_hit(int damage_enemy) {
        hp -= damage_enemy;
    }

    string get_name() {
        return nume;
    }

    int get_speed() {
        return speed;
    }

    /*
    // calculeaza distanta dintre personaje, iar daca adversarul a intrat in raza de atac
    // schimb starea de engage in "true" pentru a putea incepe atacul
    void engaged_update(Personaj Enemy)
    {
        float distanta = abs(Enemy.locatie - locatie);
        if (distanta <= range)
            //if (target == Enemy.transport || target)
            engaged = true;
    }
    */

    // inainteaza personajul in cazul in care mai traieste si
    // nu este intr-o batalie, in acest caz ar trebui sa stea
    // functia va fi apelata 1data/s si deci pot adauga la locatie
    // direct valoarea lui speed.
    void locatie_update() {
        //this_thread::sleep_for(chrono::seconds(1));
        if (hp > 0 && !engaged)
            locatie = locatie + speed;
    }

    // cauta adversari in raza sa de atac, iar daca gaseste, starea de
    // engage devine 1 si functie se opreste
    void search(char field[]) {
        for(int i=locatie-range-1; i<locatie+range; i++)
            if ((i >= 0 && field[i] != '.') || (i<=40 && field[i] != '.'))
            {
                engaged = 1;
                break;
            }
    }

    void automat(char field[], Personaj Enemy)
    {
        while (hp > 0)
        {
            search(field);
            if (engaged == 0)
            {
                locatie_update();
                afisare_camp(field, &Enemy);
                this_thread::sleep_for(chrono::seconds(1));
            }
            else
            {
                this_thread::sleep_for(chrono::milliseconds(hitspeed)); 
                Enemy.get_hit(damage);
            }
        }
        locatie = 0;
    }

    Personaj() {
        nume = "";
        hitspeed = 0;
        speed = 0;
        range = 0;
        hp = 0;
        damage = 0;
        transport = 0;
        target = 0;
        reset_factor = 0;
    }

    // cu acest constructor creez cartile disponibile
    Personaj(string in_nume, int in_hitspeed, float in_speed, float in_range, int in_hp,
        int in_damage, bool in_transport, bool in_target, bool in_reset_factor) {
        nume = in_nume;
        hitspeed = in_hitspeed;
        speed = in_speed;
        range = in_range;
        hp = in_hp;
        damage = in_damage;
        transport = in_transport;
        target = in_target;
        reset_factor = in_reset_factor;
    }

    // cu aceasta functie atribui personajul cu care ne jucam in aceasta tura
    void copy(const Personaj& jucator, float in_locatie){
        nume = jucator.nume;
        hitspeed = jucator.hitspeed;
        speed = jucator.speed;
        range = jucator.range;
        hp = jucator.hp;
        damage = jucator.damage;
        transport = jucator.transport;
        target = jucator.target;
        reset_factor = jucator.reset_factor;
        locatie = in_locatie;
    }

    // cu aceasta functie atribui adversarul cu care ne jucam in aceasta tura
    // diferenta este ca el trebuie sa mearga invers
    void copy_adv(const Personaj& jucator, float in_locatie){
        nume = jucator.nume;
        hitspeed = jucator.hitspeed;
        speed = jucator.speed;
        range = jucator.range;
        hp = jucator.hp;
        damage = jucator.damage;
        transport = jucator.transport;
        target = jucator.target;
        reset_factor = jucator.reset_factor;
        locatie = in_locatie;
        speed *= -1;
    }

    // ..W...........B..
    void afisare_camp(char field[], Personaj* Enemy)
    {
        if (Enemy->get_hp() > 0 && hp > 0)
        {
            system("CLS");
            strcpy_s(field, 42, ".........................................");
            field[(int)Enemy->locatie - 1] = Enemy->get_name()[0];
            field[(int)locatie - 1] = nume[0];
            cout << field << '\n';

            printf("\n");
            stats(*Enemy);

            //this_thread::sleep_for(chrono::seconds(1));
        }

        // dupa ce a murit un personaj
        system("CLS");
        if (Enemy->get_hp() > 0)
            printf("%s a invins!\n", Enemy->get_name().c_str());
        else
            printf("%s a invins!\n", nume.c_str());
        printf("\n");
        stats(*Enemy);
    }

    void stats(Personaj& Enemy)
    {
        printf("%s \nHP: %d \nLocatie: %.2f \nViteza: %d\n\n", Enemy.get_name().c_str(), Enemy.get_hp(), Enemy.locatie, Enemy.get_speed());
        printf("%s \nHP: %d \nLocatie: %.2f\nViteza: %d", nume.c_str(), hp, locatie, speed);
    }

};







int main() {
    Personaj Magician("Vrajitor", 1400, 3, 5.5, 656, 256, 0, 1, 0);
    Personaj Bowler("Bowler", 2500, 2, 4, 1898, 262, 0, 0, 0);
    Personaj BebeDragon("Baby Dragon", 1500, 4.5, 3.5, 1051, 146, 1, 1, 0);
    Personaj Priza("Electro Wizard", 1800, 4.5, 5, 649, 210, 0, 1, 1);

    // fara aceasta declarare de aici nu pot apela thread-ul "field"
    Personaj Enemy;
    Personaj Friendly;
    //string field(41, '.');
    char field[] = ".........................................";

    srand(time(NULL));
    int nr = rand() % 4 + 1;
    float locatie = abs(rand() % 20 + 21); // plus 21 pentru ca trebuie sa fie in a doua jumatate a sirului
    
    if (nr == 1)
        Enemy.copy_adv(Magician, locatie);
    if (nr == 2)
        Enemy.copy_adv(Bowler, locatie);
    if (nr == 3)
        Enemy.copy_adv(BebeDragon, locatie);;
    if (nr == 4)
        Enemy.copy_adv(Priza, locatie);

    nr = rand() % 4 + 1;
    locatie = abs(rand() % 20 + 1);

    if (nr == 1)
        Friendly.copy(Magician, locatie);
    if (nr == 2)
        Friendly.copy(Bowler, locatie);;
    if (nr == 3)
        Friendly.copy(BebeDragon, locatie);
    if (nr == 4)
        Friendly.copy(Priza, locatie);


        thread enemy_t(&Personaj::automat, Enemy, field, Friendly);
        thread friendly_t(&Personaj::automat, Friendly, field, Enemy);

        enemy_t.join();
        friendly_t.join();


    //thread field_t(afisare_camp, field, &Enemy, &Friendly);

    //friendly.join();
    //enemy.join();
    //field_t.join();
    /*
    while(Enemy.get_hp() > 0 && Friendly.get_hp() > 0)
    {
        afisare_camp(Enemy, Friendly);

    }
    */
    
    //field.join();
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
