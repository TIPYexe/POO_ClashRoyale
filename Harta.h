#ifndef HARTA_H
#define HARTA_H

#include <chrono>
#include <thread>

#include "Turn.h"

class Harta
{
private:

	char field[42] = {};

public:

	static int game_end(Side& Pers_Enemy, Side& Pers_Friend, Turn& Turn_Enemy, Turn& Turn_Friend);

	void afisare_camp(Side& Pers_Enemy, Side& Pers_Friend, Turn& Turn_Enemy, Turn& Turn_Friend);
    //, int nr, int nr_2, std::unique_ptr<Personaj[]> Carti
	void stats(Side &Pers_Enemy, Side &Pers_Friend, Turn &Turn_Enemy, Turn &Turn_Friend, int i);
};

#endif
