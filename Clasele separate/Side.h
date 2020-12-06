#ifndef SIDE_H
#define SIDE_H

#include "Personaj.h"

class Side : public Personaj {

private:

	int sens_deplasare;
	int locatie;

public:

	Side():
		Personaj{}, sens_deplasare{ 0 }, locatie{ 0 } {
	}
	
	Side(const Personaj& Caracter, int locatie, int sens) {
		Personaj::set_speed(sens);
		Personaj::set_locatie(locatie);
	}
};

#endif
