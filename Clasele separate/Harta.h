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

	void afisare_camp(Personaj& Enemy, Personaj& Friend);

	void stats(Personaj Enemy, Personaj Friend);
};

#endif
