#include <iostream>
#include <chrono>
#include <thread>
#include <stdlib.h>
#include <time.h>

using namespace std;
using namespace this_thread;

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

    string get_name() {
        return nume;
    }

    // calculeaza distanta dintre personaje, iar daca adversarul a intrat in raza de atac
    // schimb starea de engage in "true" pentru a putea incepe atacul
    void engaged_update(Personaj Enemy)
    {
        float distanta = abs(Enemy.locatie - locatie);
        if (distanta <= range)
            //if (target == Enemy.transport || target)
                engaged = true;
    }

    // inainteaza personajul in cazul in care mai traieste si
    // nu este intr-o batalie, in acest caz ar trebui sa stea
    // functia va fi apelata 1data/s si deci pot adauga la locatie
    // direct valoarea lui speed.
    int locatie_update() {
        if (hp > 0 && !engaged)
            locatie = locatie + speed;
    }

    Personaj();

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

    // cu acest consturctor creez personajul cu care ne jucam in aceasta tura
    Personaj(const Personaj& jucator, float in_locatie) :
        hitspeed{ jucator.hitspeed },
        speed{ jucator.speed },
        range{ jucator.range },
        hp {jucator.hp },
        damage{ jucator.damage },
        transport{ jucator.transport },
        target{ jucator.target },
        reset_factor { jucator.reset_factor }
    {
        locatie = in_locatie;
    }

    // cu acest consturctor creez adversarul cu care ne jucam in aceasta tura
    // diferenta este ca el trebuie sa mearga invers
    Personaj(const Personaj& jucator, float in_locatie, int mod_viteza) :
        hitspeed{ jucator.hitspeed },
        speed{ jucator.speed },
        range{ jucator.range },
        hp{ jucator.hp },
        damage{ jucator.damage },
        transport{ jucator.transport },
        target{ jucator.target },
        reset_factor{ jucator.reset_factor }
    {
        locatie = in_locatie;
        speed *= mod_viteza;
    }

};


// ..W...........B..
void afisare_camp(Personaj& Enemy, Personaj& Friend)
{
    //system("CLS");
    for (int i = -20; i <= 20; i++)
    {   
        if (i == Friend.locatie)
            cout << Friend.get_name()[0];
        else if (i == Enemy.locatie)
            cout << Enemy.get_name()[0];
        else
            cout << ".";
    }
    cout << '\n';
}


int main() {
    Personaj Magician("Vrajitor", 1400, 3, 5.5, 656, 256, 0, 1, 0);
    Personaj Bowler("Bowler", 2500, 2, 4, 1898, 262, 0, 0, 0);
    Personaj BebeDragon("Baby Dragon", 1500, 4.5, 3.5, 1051, 146, 1, 1, 0);
    Personaj Priza("Electro Wizard", 1800, 4.5, 5, 649, 210, 0, 1, 1);
    
    // fara aceasta declarare de aici nu pot apela thread-ul "field"
    Personaj Enemy;
    Personaj Friendly;

    srand(time(NULL));
    int nr = rand() % 4 + 1;
    float locatie = abs(rand() % 20 + 1);

    if (nr == 1)
        Personaj Enemy = Personaj(Magician, locatie, -1);
    if (nr == 2)
        Personaj Enemy = Personaj(Bowler, locatie, -1);
    if (nr == 3)
        Personaj Enemy = Personaj(BebeDragon, locatie, -1);
    if (nr == 4)
        Personaj Enemy = Personaj(Priza, locatie, -1);

    nr = rand() % 4 + 1;
    locatie = 0 - abs(rand() % 20 + 1);

    if (nr == 1)
        Personaj Friendly = Personaj(Magician, locatie);
    if (nr == 2)
        Personaj Friendly = Personaj(Bowler, locatie);
    if (nr == 3) 
        Personaj Friendly = Personaj(BebeDragon, locatie);
    if (nr == 4) 
        Personaj Friendly = Personaj(Priza, locatie);

    //thread field(afisare_camp, &Enemy, &Friendly);

    /*
    while(Enemy.get_hp() > 0 && Friendly.get_hp() > 0)
    { 
        afisare_camp(Enemy, Friendly);
        
    }
    */

    cout << Enemy.get_name()[0];

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
