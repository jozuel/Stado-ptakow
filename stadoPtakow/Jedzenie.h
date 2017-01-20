#pragma once
#include "Obiekt.h"
class Jedzenie : public Obiekt
{

public:
	std::string wypiszTyp();
	Jedzenie();
	Jedzenie(double x, double y);
	~Jedzenie();
};

