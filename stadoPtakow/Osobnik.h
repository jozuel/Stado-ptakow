#pragma once
#include "Ptak.h"
class Osobnik : public Ptak
	
{
private:
	bool czyGlodny;
	bool czywStadzie;
	bool ucieczka;
public:
	Osobnik();
	Osobnik(double x, double y);
	~Osobnik();
	void poruszanie();
	void uciekaj();
	std::string wypiszTyp();
};

