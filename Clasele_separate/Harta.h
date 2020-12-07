#ifndef HARTA_H
#define HARTA_H

#include <chrono>
#include <thread>

#include "Personaj.h"
#include "Turn.h"

class Personaj;

class Harta
{
private:

	char field[42] = {};

public:

	int game_end(Personaj& Enemy, Personaj& Friend, Turn& Inamic, Turn& Prieten);

	void afisare_camp(Personaj& Enemy, Personaj& Friend, Turn& Inamic, Turn& Prieten);

	void stats(Personaj Enemy, Personaj Friend, Turn Inamic, Turn Prieten, int i);
};

#endif
