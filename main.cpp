#include <iostream>
#include <chrono>
#include <thread>
#include <stdlib.h>
#include <time.h>
#include <string.h>

using namespace std;
using namespace this_thread;
//using namespace chrono;

class Personaj
{
private:

    // calitati personaj
    int hitspeed; // timp (milisecunde) de charge pentru atac
    int speed; // viteza de deplasare per secunda
                 // pentru  a-mi simplifica viata, campul de lupta este axa numerelor
                 // iar adversarului ii voi da o viteza negativa, pentru a face personajele
                 // sa se apropie

    float range; // distanta de la care poate ataca
    int hp; // puncte de viata 
    int damage; // puncte de viata pe care le ia per atac
    bool transport; // 0 = teren; 1 = aer
    bool target; // 0 = ataca doar teren; 1 = ataca teren & aer
    bool reset_factor; // daca atacul lui are si efect de reset asupra atacului
                       // inamicului
    int locatie; // locatia pe campul de lupta (axa numerelor)
    
    // statistici lupta
    bool engaged; // 0 = nu se lupta; 1 = se lupta

    string nume;

public:

    int get_locatie() {
        return locatie;
    }

    int get_hp() {
        return hp;
    }

    string get_name() {
        return nume;
    }

    int get_speed(){
        return speed;
    }

    int get_damage(){
        return damage;
    }

    bool get_transport() {
        return transport;
    }

    void get_hit(int damage_enemy) {
        //cout << nume << " si-a luat damage. HP: " << hp <<"\n";
        hp -= damage_enemy;
    }

    // inainteaza personajul in cazul in care mai traieste si
    // nu este intr-o batalie, in acest caz ar trebui sa stea
    // functia va fi apelata 1data/s si deci pot adauga la locatie
    // direct valoarea lui speed.
    void locatie_update() {
        if (hp > 0)
            locatie += speed;
        if (locatie < 0)
            locatie = 0;
        if (locatie > 40)
            locatie = 40;
    }

    // cauta adversari in raza sa de atac, iar daca gaseste, starea de
    // engage devine 1 si functie se opreste
    void search(char field[])
    {
        for (int i = locatie - range - 1; i < locatie + range; i++)
        {
            if(i>=0 && i<=40 && i!=(locatie-1))
                if (field[i] != '.')
                {
                    engaged = 1;
                    break;
                }
        }
    }

    void automat(char field[], Personaj& Enemy);

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
        engaged = 0;
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

};

void stats(Personaj Enemy, Personaj Friend)
{
    printf("%s \nHP: %d \nDamage: %d \nLocatie: %d \nViteza: %d\n\n", Enemy.get_name().c_str(), Enemy.get_hp(),
                                                                      Enemy.get_damage(), Enemy.get_locatie(), Enemy.get_speed());
    printf("%s \nHP: %d \nDamage: %d \nLocatie: %d \nViteza: %d\n", Friend.get_name().c_str(), Friend.get_hp(),
                                                                    Friend.get_damage(), Friend.get_locatie(), Friend.get_speed());
}

// cam asa va arata harta 1D: ..W...........B..
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


// a trebuit sa creez functia in afara metodei pentru ca altfel nu gasea functia "afisare_camp"
void Personaj::automat(char field[], Personaj& Enemy)
{
    while (Enemy.get_hp() > 0 && hp > 0)
    {   
        if (engaged == 0)
        {
            search(field); //separ un search de locatie_update pt ca altfel ar face un pas
                           //chiar daca s-au spawnat unul langa altul
            if (engaged == 0) //verific daca a devenit engaged pt a nu face pasi in plus
            {
                locatie_update();
                sleep_for(chrono::seconds(1)); //viteza pasilor e masurata pe secunda
            }
        }
        else
        {
            sleep_for(chrono::milliseconds(hitspeed)); //mai intai trebuie sa treaca 
                                                       //timpul de charge al atacului
            if((Enemy.get_transport() == target) || target) //verific daca il poate ataca
                Enemy.get_hit(damage);
        }
    }
}


int main() {
    
    Personaj Carti[5];
    Carti[0] = Personaj("Vrajitor", 1400, 3, 5.5, 656, 256, 0, 1, 0);
    Carti[1] = Personaj("Bowler", 2500, 2, 4, 1898, 262, 0, 0, 0);
    Carti[2] = Personaj("Baby Dragon", 1500, 4, 3.5, 1051, 146, 1, 1, 0);
    Carti[3] = Personaj("Electro Wizard", 1800, 4, 5, 649, 210, 0, 1, 1);

    // fara aceasta declarare de aici nu pot apela thread-ul "field"
    Personaj Enemy;
    Personaj Friendly;
    char field[] = ".........................................";

    srand(time(NULL));
    int nr = rand() % 4;
    float locatie = abs(rand() % 20 + 21); // +21 pt ca trebuie sa fie in a doua jumatate
    Enemy.copy_adv(Carti[nr], locatie);

    nr = rand() % 4;
    locatie = abs(rand() % 20 + 1);
    Friendly.copy(Carti[nr], locatie);
    

    // fiecare meteoda si functia de afisare a hartii+stats ruleaza pe cate un thread
    // pentru ca toate aceste functii trebuie sa ruleze simultan
    thread enemy(&Personaj::automat, ref(Enemy), field, ref(Friendly));     // am pasat obiectele ca referinte pentru ca altfel
    thread friendly(&Personaj::automat, ref(Friendly), field, ref(Enemy));  // nu se modificau valorile, si deci nu aveau relevanta 
    thread field_t(afisare_camp, field, ref(Enemy), ref(Friendly));         // nici harta nici statisticile, ramaneau neschimbate

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
