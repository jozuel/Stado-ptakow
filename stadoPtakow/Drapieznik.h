#pragma once
#include "Ptak.h"
class Drapieznik : public Ptak
{
private:
	bool znalezionoOfiare;
	
public:
	std::string wypiszTyp();
	void ruch(std::vector<Obiekt*>tab, double tangens[], double zasiegWidzenia, double rozmiarOsobnika);
	void poruszanieDoObiektu(Obiekt* innyObiekt, double rozmiarOsobnika);
	Drapieznik();
	Drapieznik(double x, double y, double vx, double vy);
	Drapieznik(double x, double y);

	~Drapieznik();
};

